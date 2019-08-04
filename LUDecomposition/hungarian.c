#include "hungarian.h"


#include "libfpanrio.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define dtfp(v) doubleToFpanr(v)
#define fptd(v) fpanrToDouble(v)
#define FPANR_ZERO isFpanr?dtfp(0.0):0.0
#define FPANR_ONE isFpanr?dtfp(1.0):1.0
// #define FPANR_ZERO 0.0
// #define FPANR_ONE 1.0
#define TO_FP(v) isFpanr?fptd(v):v

#define TRUE 1
#define FALSE 0

//#define DEBUG

enum HUNG_STEPS{HS_PRELIMINARIES, HS_ONE, HS_TWO, HS_THREE, HS_END};

/**
 * Print a matrix to stdout
 * @param x number of lines
 * @param y number of columns
 * @param matrix the matrix to print
 */
/*void matrix_print_fpanr (const size_t x, const size_t y, const double matrix[x][y])
{
  for(size_t i=0; i<x; ++i)
  {
    for(size_t j=0; j<y; ++j)
    {
      char * chaine = fpanrDoubleToStr(matrix[i][j]);
      printf ( "%s\t", chaine );
      free(chaine);
    }
    printf("\n");
  }
}*/

int hungarian(const size_t n, const size_t m, double inputMat[n][m], size_t independantSet[MIN(n,m)][2], short int isFpanr) {
  double matrix[n][m];
  memcpy(matrix, inputMat, sizeof(double)*(n*m));
  double minH;
  short int starred[n][m], coveredRows[n], coveredColumns[m], primed[n][m];
  short int isStarred = FALSE, isFound = FALSE, isCovered = FALSE, isMin = FALSE;
  size_t i,j,k;
  short int bStep1 = TRUE/*, step2 = FALSE, step3 = FALSE*/;
  size_t sequence[n*m][2];
  size_t zRow, zColumn;
  short int shouldExit = FALSE;
  enum HUNG_STEPS state = HS_PRELIMINARIES;
  size_t cpt;
  int bla;
  size_t index;

  #ifdef DEBUG
    printf("stepA\n");
    //scanf("%c",&bStep1);
    fflush(stdout);
  #endif

  while(!shouldExit) {
    switch(state) {
      case HS_PRELIMINARIES:
      // PRELIMINARIES
      // no lines are covered
      memset( coveredRows, FALSE, n*sizeof(short int) );
      memset( coveredColumns, FALSE, m*sizeof(short int) );
      // no zeros are starred or primed
      memset( starred, FALSE, n*m*sizeof(short int) );
      memset( primed, FALSE, n*m*sizeof(short int) );
      // consider a row of the matrix A 
      for ( i = 0 ; i < n ; ++i ) {
        // substract from each element in this row the smallest element of this row
        minH = matrix[i][0];
        for ( j = 1 ; j < m ; ++j ) {
          if ( matrix[i][j] < minH ) {
            minH = matrix[i][j];
          }
        }
        for ( j = 0 ; j < m ; ++j ) {
          matrix[i][j] -= minH;
        }
      } // do the same for each row of A

      #ifdef DEBUG
        printf("stepB\n");
        fflush(stdout);
      #endif

      // consider a column of the matrix A 
      for ( j = 0 ; j < m ; ++j ) {
        // substract from each element in this column the smallest element of this column
        minH = matrix[0][j];
        for ( i = 1 ; i < n ; ++i ) {
          if ( matrix[i][j] < minH ) {
            minH = matrix[i][j];
          }
        }
        for ( i = 0 ; i < n ; ++i ) {
          matrix[i][j] -= minH;
        }
      } // do the same for each column of A
      #ifdef DEBUG
        printf("stepC\n");
        fflush(stdout);
      #endif
      for ( i = 0 ; i < n ; ++i ) {
        for ( j = 0 ; j < m ; ++j ) {
          // consider a zero Z of the matrix
          if (cmpFpanrDouble(matrix[i][j],FPANR_ZERO) == 0 ) {
            // if there is no starred zero in its row
            isStarred = rowContainsTrue(n,m,i,starred);
            // and none in its column
            isStarred = isStarred || columnContainsTrue(n,m,j,starred);
            // /!\!
            if ( !isStarred ) {
              // star Z
              starred[i][j] = TRUE;
            }
          } // repeat, considering each zero in the matrix in turn
        }
      }
      #ifdef DEBUG
        printf("stepD\n");
        cusPrintM(n,m,starred);
        cusPrintM(n,m,primed);
        fflush(stdout);
      #endif
      isCovered = TRUE;
      // then cover every column containing a starred zero
      for ( j = 0 ; j < m ; ++j ) {
        isStarred = columnContainsTrue(n,m,j,starred);
        #ifdef DEBUG
        printf("\nisCovered=%hd",isCovered);
        // scanf("%hd",&bStep1);
        #endif
        isCovered = isCovered && isStarred;
        if (isStarred) {
          coveredColumns[j] = TRUE;
        }
      }
      #ifdef DEBUG
        printf("before while step1\n");
        fflush(stdout);
      #endif
      if ( isCovered ) 
        state = HS_END;
      else
        state = HS_ONE;
      break;
    // --------------------------------------------------------
      //              STEP    1
    // --------------------------------------------------------
    case HS_ONE:
      bStep1 = TRUE;
      while(bStep1) {
        // STEP 1
        #ifdef DEBUG
          printf("\n--------------\nSTEP1\n");
          // scanf("%d",&bla);
          fflush(stdout);
        #endif
        isCovered = FALSE;
        for ( i = 0 ; i < n ; ++i ) {
          for ( j = 0 ; j < m ; ++j ) {
          #ifdef DEBUG
            printf("%f ",matrix[i][j]);
            printf("\nStep1:%zu %zu",i,j);
            cusPrintA(n,coveredRows);
            cusPrintA(m,coveredColumns);
            cusPrintM(n,m,starred);
            fflush(stdout);
            // scanf("%d",&bla);
          #endif
            // char * chaine = fpanrDoubleToStr(matrix[i][j]);
            // printf("\n!%s vs %3.53f ? %d vs %d\n",chaine, TO_FP(matrix[i][j]),cmpFpanrDouble(matrix[i][j],FPANR_ZERO)==0, 1==2);
            // free(chaine);
            // choose a non-covered zero
          //  if (TO_FP(matrix[i][j]) == FPANR_ZERO && coveredRows[i] == FALSE && coveredColumns[j] == FALSE) {
            if (cmpFpanrDouble(matrix[i][j], FPANR_ZERO) == 0 && coveredRows[i] == FALSE && coveredColumns[j] == FALSE) {
            #ifdef DEBUG
              printf("\nWAZAAAAAAAAa:%zu %zu",i,j);
              cusPrintA(n,coveredRows);
              cusPrintA(m,coveredColumns);
              cusPrintM(n,m,starred);
              fflush(stdout);
              // scanf("%d",&bla);
            #endif
              // and prime it
              primed[i][j] = TRUE;
              // consider the row containing it (i)
              isStarred = rowContainsTrue(n,m,i,starred);
              // if there is no starred zero in this row
              if ( !isStarred ) {
                // go at once to step 2
                bStep1 = FALSE;
                state = HS_TWO;
              } else { // if there is a starred zero Z in this row
                // cover this row
                coveredRows[i] = TRUE;
                for ( k = 0 ; k < m ; ++k ) {
                  if ( starred[i][k] == TRUE) {
                    // and uncover the column of Z
                    coveredColumns[k] = FALSE;
                  } // is Z starred?
                } // selecting column of z
              } // starred 0 is this row?
            } // non covered zero ?
          } // for columns
        } // for lines
        if(bStep1) {
          isCovered = TRUE;
          for ( i = 0 ; i < n && isCovered ; ++i ) {
            for (j = 0 ; j < m && isCovered ; ++j ) {
              if ( cmpFpanrDouble(matrix[i][j], FPANR_ZERO) == 0 && coveredRows[i] == FALSE && coveredColumns[j] == FALSE) {
                isCovered = FALSE;
              }
            }
          } 
          bStep1 = !isCovered;
        }
      } // repeat until all zeros are covered (bStep1)
      if ( state == HS_ONE) 
        state = HS_THREE;
      // end of step1
      fflush(stdin);
      fflush(stdout);
      // scanf("%d",&bla);
      fflush(stdin);
      fflush(stdout);
      break;
    // --------------------------------------------------------
      //              STEP    2
    // --------------------------------------------------------
    case HS_TWO:
      printf("\n--------------\nSTEP2\n");
      // STEP 2
      isFound = FALSE;
      for ( i = 0 ; i < n && !isFound ; ++i ) {
        for ( j = 0 ; j < m && !isFound; ++j ) {
          if ( coveredRows[i] == FALSE && coveredColumns[j] == FALSE && primed[i][j] == TRUE ) {
            sequence[0][0] = i;
            sequence[0][1] = j;
            isFound = TRUE;
          }
        }
      }
      isStarred = TRUE;
      index = 1;
      while ( isStarred ) {
        cusPrintMZu(index,2,sequence);
        isFound = FALSE;
        zColumn = sequence[index-1][1];
        for ( i = 0 ; i < n && !isFound ; ++i ) {
          if ( starred[i][zColumn] == TRUE ) {
            sequence[index][0] = i;
            sequence[index][1] = zColumn;
            index++;
            isFound = TRUE;
          }
        }
        zRow = sequence[index-1][0];
        if ( isFound ) {
          isFound = FALSE;
          for ( j = 0 ; j < m && !isFound ; ++j ) {
            if ( primed[zRow][j] == TRUE ) {
              sequence[index][0] = zRow;
              sequence[index][1] = j;
              index++;
              isFound = TRUE;
            }
          }
        } else {
          isStarred = FALSE;
        }
      }
      for ( k = 0 ; k < index ; ++k ) {
        zRow = sequence[k][0];
        zColumn = sequence[k][1];
          // unstar each starred zero of the sequence
        if (starred[zRow][zColumn] == TRUE) {
          starred[zRow][zColumn] = FALSE;
        }
      }
      for ( k = 0 ; k < index ; ++k ) {
        zRow = sequence[k][0];
        zColumn = sequence[k][1];
        // star each primed zero of the sequence
        if (primed[zRow][zColumn] == TRUE) {
          starred[zRow][zColumn] = TRUE;
        }
      }
      for ( i = 0 ; i < n ; ++i ) {
        // erase all primes
        setRow(n,m,i,primed,FALSE);
        // uncover every row
        coveredRows[i] = FALSE;
      }
      // cover every column ...
      for( j = 0 ; j < m ; ++j ) {
        // containing a 0*
        if ( columnContainsTrue(n, m, j, starred) ) {
          coveredColumns[j] = TRUE;
        }
      }
      isCovered = TRUE;
      for( j = 0 ; j < m && isCovered ; ++j ) {
        isCovered = isCovered && isCoveredColumn(m,j,coveredColumns);
      }
      if ( isCovered ) {
          // if all column are covered, the starred 0 form the independant set
        #ifdef DEBUG
          printf("Found the independant set\n");
          fflush(stdout);
        #endif
        state = HS_END;
      } else {
        state = HS_ONE;
      }
      // end of STEP 2
      break;
    // --------------------------------------------------------
      //              STEP    3
    // --------------------------------------------------------
    case HS_THREE:
      #ifdef DEBUG
        printf("\n--------------\nSTEP3\n");
        cusPrintA(n,coveredRows);
        cusPrintA(m,coveredColumns);
        fflush(stdout);
        for ( i = 0 ; i < n ; ++i ) {
          for( j = 0 ; j < m ; ++j ) {
            assert(cmpFpanrDouble(matrix[i][j], FPANR_ZERO) != 0 || (coveredRows[i] || coveredColumns[j]) 
            /* "At this point, all the zeros of the matrix are covered"*/);
          }
        }
      #endif
      // let h denote the smallest non-covered element of the matrix
      isMin = FALSE;
      for ( i = 0 ; i < n ; ++i ) {
        if(coveredRows[i] == FALSE) {
          for ( j = 0 ; j < m ; ++j ) {
            if ( coveredColumns[j] == FALSE ) {
              if(!isMin) {
                minH = matrix[i][j];
                isMin = TRUE;
              } else {
                if ( matrix[i][j] < minH ) {
                  minH = matrix[i][j];
                }
              }
            }
          }
        }
      }
      #ifdef DEBUG
        printf("h=%f\n",minH);
      #endif
      // add h to each covered row
      for ( i = 0 ; i < n ; ++i ) {
        if(isCoveredRow(n,i,coveredRows)) {
          for ( j = 0 ; j < m ; ++j ) {
            matrix[i][j] += minH;
          }
        }
      }
      // substract h from each uncovered column
      for ( j = 0 ; j < m ; ++j ) {
        if(!isCoveredColumn(m,j,coveredColumns)) {
          for ( i = 0 ; i < n ; ++i ) {
            matrix[i][j] -= minH;
          }
        }
      }
      state = HS_ONE;
     // end of step 3
      break;
    case HS_END:
      cpt = 0;
      for( i = 0 ; i < n ; ++i ) {
        for ( j = 0 ; j < m ; ++j ) {
          if ( starred[i][j] == TRUE ) {
            independantSet[cpt][0] = i;
            independantSet[cpt][1] = j;
            cpt++;
          }
        }
      }
      shouldExit = TRUE;
      break;
    } // switch
  } // while should exit
  // end
#ifdef DEBUG
  printf("EOF\n");
  fflush(stdout);
#endif
  return 0;
}



short int rowContainsTrue(const size_t n, const size_t m, const size_t row, const short int matrix[n][m]) {
  short int isStarred = FALSE;
  for ( size_t k = 0 ; k < m && !isStarred ; ++k ) {
    if ( matrix[row][k] == TRUE ) {
      isStarred = TRUE;
    }
  }
  return isStarred;
}

short int columnContainsTrue(const size_t n, const size_t m, const size_t column, const short int matrix[n][m]) {
  short int isStarred = FALSE;
  for ( size_t k = 0 ; k < n && !isStarred ; ++k ) {
    if ( matrix[k][column] == TRUE ) {
      isStarred = TRUE;
    }
  }
  return isStarred;
}

void setRow(const size_t n, const size_t m, const size_t row, short int matrix[n][m], const short int val) {
  for ( size_t j = 0 ; j < m ; ++j ) {
    matrix[row][j] = val;
  }
}

void setColumn(const size_t n, const size_t m, const size_t column, short int matrix[n][m], const short int val) {
  for ( size_t i = 0 ; i < n ; ++i ) {
    matrix[i][column] = val;
  }
}

short int isCoveredRow(const size_t n, const size_t row, const short int matrix[n]) {
  short int found = TRUE;
  found = (matrix[row] == TRUE);
  // for ( size_t j = 0 ; j < m && found == TRUE ; ++j ) {
  //   if (matrix[row][j]==FALSE) {
  //     found = FALSE;
  //   }
  // }
  return found;
}

short int isCoveredColumn(const size_t m, const size_t column, const short int matrix[m]) {
  short int found = TRUE;
  found = (matrix[column] == TRUE);
  // for ( size_t i = 0 ; i < n && found == TRUE ; ++i ) {
  //   if (matrix[i][column]==FALSE) {
  //     found = FALSE;
  //   }
  // }
  return found;
}

void cusPrintA(const size_t n, const short int a[n]) {
  for ( size_t i = 0 ; i < n ; ++i ) {
    printf("%hd\t",a[i]);
  }
}

void cusPrintM(const size_t n, const size_t m, const short int mat[n][m]) {
  for (size_t i = 0 ; i < n ; ++i ) {
    for (size_t j = 0 ; j < m ; ++j ) {
      printf("%hd\t",mat[i][j]);
    }
    printf("\n");
  }
}

void cusPrintMZu(const size_t n, const size_t m, const size_t mat[n][m]) {
  for (size_t i = 0 ; i < n ; ++i ) {
    for (size_t j = 0 ; j < m ; ++j ) {
      printf("%zu\t",mat[i][j]);
    }
    printf("\n");
  }
}