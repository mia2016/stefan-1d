set terminal png enhanced size 1000, 1000
set output "kontur.png"

set view map

set xlabel "Tid [dager]"
set ylabel "Dybde [m]"
set cblabel "Temperatur [K]"

set xtics nomirror
set ytics nomirror

set border 26

set datafile missing "0.000000"
splot "temp.out" matrix u ($2/10.0):($1/201.0):3 with pm3d notitle,\
     "log.out" u 1:208:(270) lw 3 lc "blue" w l t "Isdybde",\
     "log.out" u 1:211:(270) lw 3 lc "red" w l t "Snødybde"
