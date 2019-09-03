clear
set multiplot
set size 1, 0.5
set origin 0.0,0.0
plot 'output/hungPRECref_n3_MAX_MAG_IN_S.dat' using 1:2 with boxes fill pattern 1, '' u 1:($2 + 0.25):($2) with labels    
set title "Gauss - fig2 - Most precise element in S"
set xlabel "Precision (computed using FPANR)"
set ylabel "Distribution"
set origin 0.0,0.5
plot 'output/hungPRECref_n3_MAX_PREC.dat' using 1:2 with boxes fill pattern 1, '' u 1:($2 + 0.25):($2) with labels
set title "Gauss - fig2 - Maximum magnitude in S" 
set xlabel "Precision (computed using FPANR)"
set ylabel "Distribution"
unset multiplot