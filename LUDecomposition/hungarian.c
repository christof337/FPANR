#include "hungarian.h"

#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define DEBUG

int hungarian(const size_t n, const size_t m, double matrix[n][m], size_t independantSet[MIN(n,m)][2]) {
  double minH;
  short int starred[n][m], coveredRows[n], coveredColumns[m], primed[n][m];
  short int isStarred = FALSE, isFound = FALSE, isCovered = FALSE, isMin = FALSE;
  size_t i,j,k;
  short int bStep1 = TRUE/*, step2 = FALSE, step3 = FALSE*/;
  size_t sequence[n*m][2];
  size_t zRow, zColumn;

#ifdef DEBUG
  printf("stepA\n");
  //scanf("%c",&bStep1);
  fflush(stdout);
#endif

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
      if (matrix[i][j]==0.0) {
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
  fflush(stdout);
#endif
  // then cover every column containing a starred zero
  for ( j = 0 ; j < m ; ++j ) {
    isStarred = columnContainsTrue(n,m,j,starred);
    if (isStarred) {
      coveredColumns[j] = TRUE;
    }
  }
  #ifdef DEBUG
    printf("before while step1\n");
    fflush(stdout);
  #endif
step1:
  while(bStep1) {
      // STEP 1
  #ifdef DEBUG
    printf("Step1\n");
    fflush(stdout);
  #endif
    isCovered = FALSE;
    for ( i = 0 ; i < n ; ++i ) {
      for ( j = 0 ; j < m ; ++j ) {
        // choose a non-covered zero
        if (matrix[i][j] == 0.0 && coveredRows[i] == FALSE && coveredColumns[j] == FALSE) {
            // and prime it
          primed[i][j] = TRUE;
            // consider the row containing it (i)
          isStarred = rowContainsTrue(n,m,i,starred);
            // if there is no starred zero in this row
          if ( !isStarred ) {
            // go at once to step 2
            bStep1 = FALSE;
            goto step2;
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
    }
    isCovered = TRUE;
    for ( i = 0 ; i < n && isCovered ; ++i ) {
      for (j = 0 ; j < m && isCovered ; ++j ) {
        if ( matrix[i][j] == 0.0 && coveredRows[i] == FALSE && coveredColumns[j] == FALSE) {
          isCovered = FALSE;
        }
      }
    } 
    bStep1 = !isCovered;
  } // repeat until all zeros are covered
  goto step3;
  // end of step1
step2:
    // STEP 2
  #ifdef DEBUG
    printf("step2\n");
    scanf("%d",&bStep1);
    fflush(stdout);
  #endif
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
  size_t index = 1;
  while ( isStarred ) {
    isFound = FALSE;
    zRow = sequence[index-1][0];
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
    zColumn = sequence[index-1][1];

    if ( isFound ) {
      isFound = FALSE;
      for ( j = 0 ; j < m && !isFound ; ++j ) {
        if ( primed[i][j] == TRUE ) {
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
  for( j = 0 ; j < m ; ++j ) {
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
    bStep1 = FALSE;
    size_t cpt = 0;
    for( i = 0 ; i < n ; ++i ) {
      for ( j = 0 ; j < m ; ++j ) {
        if ( starred[i][j] == TRUE ) {
          independantSet[cpt][0] = i;
          independantSet[cpt][1] = j;
        }
      }
    }
    goto endOfHung;
  } else {
    bStep1 = TRUE;
    goto step1;
  }
  // end of STEP 2
step3:
#ifdef DEBUG
  printf("Step3\n");
  fflush(stdout);
#endif
  // let h denote the smallest non-covered element of the matrix
  isMin = FALSE;
  for ( i = 0 ; i < n ; ++i ) {
    for ( j = 0 ; j < m ; ++j ) {
      if ( coveredRows[i] == FALSE && coveredColumns[j] == FALSE ) {
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
  printf("h=%f",minH);
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
  bStep1 = TRUE;
  goto step1;
 // end of step 3
endOfHung:
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