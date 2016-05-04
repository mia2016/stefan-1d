#set term wxt
set terminal png enhanced size 1000, 1200
set output "kontur_grid.png"

set xlabel "Tid [dager]" offset 0, 0
set ylabel "Dybde [m]" offset 0.7, 0
set cblabel "Temperatur [K]" offset -9, 0

set multiplot layout 3, 2

set datafile missing "0.000000"
set view map

set xrange [0:24]
set yrange [0:1]
set cbrange [245:275]

set xtics 4 nomirror
set ytics nomirror

set border 26

set lmargin 8
set rmargin 8
set tmargin 2
set bmargin 2

set title "a)" font ",25" offset -15, 0
splot "results/ultra_1/temp.out" matrix u ($2/10.0):($1/201.0):3 with pm3d notitle,\
    "results/ultra_1/log.out" u 1:208:(270) lw 3 lc "blue" w l t "Isdybde",\
    "results/ultra_1/log.out" u 1:211:(270) lw 3 lc "red" w l t "Total dybde"
set title "b)"
splot "results/ultra_05/temp.out" matrix u ($2/10.0):($1/402.0):3 with pm3d notitle,\
    "results/ultra_05/log.out" u 1:208:(270) lw 3 lc "blue" w l t "Isdybde",\
    "results/ultra_05/log.out" u 1:211:(270) lw 3 lc "red" w l t "Total dybde"
set title "c)"
splot "results/high_1/temp.out" matrix u ($2/10.0):($1/201.0):3 with pm3d notitle,\
    "results/high_1/log.out" u 1:208:(270) lw 3 lc "blue" w l t "Isdybde",\
    "results/high_1/log.out" u 1:211:(270) lw 3 lc "red" w l t "Total dybde"
set title "d)" 
splot "results/high_05/temp.out" matrix u ($2/10.0):($1/402.0):3 with pm3d notitle,\
    "results/high_05/log.out" u 1:208:(270) lw 3 lc "blue" w l t "Isdybde",\
    "results/high_05/log.out" u 1:211:(270) lw 3 lc "red" w l t "Total dybde"
set title "e)" 
set cblabel "Temperatur [K]" offset -11, 0
splot "results/low_1/temp.out" matrix u ($2/10.0):($1/201.0):3 with pm3d notitle,\
    "results/low_1/log.out" u 1:208:(270) lw 3 lc "blue" w l t "Isdybde",\
    "results/low_1/log.out" u 1:211:(270) lw 3 lc "red" w l t "Total dybde"
set title "f)" 
splot "results/low_05/temp.out" matrix u ($2/10.0):($1/402.0):3 with pm3d notitle,\
    "results/low_05/log.out" u 1:208:(270) lw 3 lc "blue" w l t "Isdybde",\
    "results/low_05/log.out" u 1:211:(270) lw 3 lc "red" w l t "Total dybde"
