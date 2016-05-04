#set term wxt
set terminal png enhanced size 1200, 1500
set output "kontur_grid.png"

set xlabel "Tid [dager]" offset 0, 0
set ylabel "Dybde [m]" offset 0.7, 0
set cblabel "Temperatur [K]" offset -9, 0

set multiplot layout 3, 2

set datafile missing "0.000000"
set view map

set xrange [0:12]
set yrange [0:1]
set cbrange [264:274]

set xtics nomirror
set ytics nomirror

set border 26

splot "results/high_1/temp.out" matrix u ($2/10.0):($1/201.0):3 with pm3d notitle,\
    "results/high_1/log.out" u 1:208:(270) lw 3 lc "blue" w l t "Isdybde",\
    "results/high_1/log.out" u 1:211:(270) lw 3 lc "red" w l t "Snødybde"
splot "results/high_05/temp.out" matrix u ($2/10.0):($1/402.0):3 with pm3d notitle,\
    "results/high_05/log.out" u 1:208:(270) lw 3 lc "blue" w l t "Isdybde",\
    "results/high_05/log.out" u 1:211:(270) lw 3 lc "red" w l t "Snødybde"
splot "results/middle_1/temp.out" matrix u ($2/10.0):($1/201.0):3 with pm3d notitle,\
    "results/middle_1/log.out" u 1:208:(270) lw 3 lc "blue" w l t "Isdybde",\
    "results/middle_1/log.out" u 1:211:(270) lw 3 lc "red" w l t "Snødybde"
splot "results/middle_05/temp.out" matrix u ($2/10.0):($1/402.0):3 with pm3d notitle,\
    "results/middle_05/log.out" u 1:208:(270) lw 3 lc "blue" w l t "Isdybde",\
    "results/middle_05/log.out" u 1:211:(270) lw 3 lc "red" w l t "Snødybde"
splot "results/low_1/temp.out" matrix u ($2/10.0):($1/201.0):3 with pm3d notitle,\
    "results/low_1/log.out" u 1:208:(270) lw 3 lc "blue" w l t "Isdybde",\
    "results/low_1/log.out" u 1:211:(270) lw 3 lc "red" w l t "Snødybde"
splot "results/low_05/temp.out" matrix u ($2/10.0):($1/402.0):3 with pm3d notitle,\
    "results/low_05/log.out" u 1:208:(270) lw 3 lc "blue" w l t "Isdybde",\
    "results/low_05/log.out" u 1:211:(270) lw 3 lc "red" w l t "Snødybde"
