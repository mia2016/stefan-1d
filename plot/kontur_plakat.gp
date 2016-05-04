#set term wxt
set terminal png enhanced size 800, 1200
set output "kontur_plakat.png"

set xlabel "Tid [dager]" offset 0, 0
set ylabel "Dybde [m]" offset 0, 0
set cblabel "Temperatur [K]" offset -12, 0

set multiplot layout 2, 1

set datafile missing "0.000000"
set view map

set xrange [0:24]
set yrange [0:1]
set cbrange [245:275]

set xtics 4 nomirror
set ytics nomirror

set border 26

set title "a)" font ",25" offset -25, 0
splot "results/ultra_1/temp.out" matrix u ($2/10.0):($1/201.0):3 with pm3d notitle,\
    "results/ultra_1/log.out" u 1:208:(270) lw 3 lc "blue" w l t "Isdybde",\
    "results/ultra_1/log.out" u 1:211:(270) lw 3 lc "red" w l t "Total dybde"
set title "b)"
splot "results/low_1/temp.out" matrix u ($2/10.0):($1/201.0):3 with pm3d notitle,\
    "results/low_1/log.out" u 1:208:(270) lw 3 lc "blue" w l t "Isdybde",\
    "results/low_1/log.out" u 1:211:(270) lw 3 lc "red" w l t "Total dybde"
