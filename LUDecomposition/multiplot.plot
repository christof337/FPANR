set multiplot
set size 1, 0.33
set origin 0.0,0.66
plot 'output/hungPRECref_n3_MAX_MAG_NOT_IN_S.dat' using 1:2 with boxes fill pattern 1, '' u 1:($2 + 0.5):($2) with labels      
set origin 0.0,0.33
plot 'output/hungPRECref_n3_MAX_MAG_IN_S.dat' using 1:2 with boxes fill pattern 1, '' u 1:($2 + 0.5):($2) with labels                                                                  
set origin 0.0,0.0
plot 'output/hungPRECref_n3_MAX_PREC.dat' using 1:2 with boxes fill pattern 1, '' u 1:($2 + 0.5):($2) with labels
unset multiplot
