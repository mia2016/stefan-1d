#set term wxt
set terminal png enhanced size 1000, 1200
set output "plakat.png"
set hidden3d
set pm3d
set palette

set key left font ",30"
set multiplot layout 2, 1

set view 120, 140

set datafile missing "0.000000"

set xlabel "Posisjon [m]"
set ylabel "Tid [dager]"
set zlabel "Temperatur [K]" rotate by 90

set xrange [0:1]
set yrange [0:10]
set zrange [264:274]
set cbrange [264:274]

set cbtics 3 
set xtics 0.2 nomirror
set ytics 2 nomirror
set ztics 3 nomirror

set border 26

splot "results/high_1/temp.out" matrix u ($1/21.0):($2/10.0):3 with pm3d t "a)"
splot "results/low_1/temp.out" matrix u ($1/21.0):($2/10.0):3 with pm3d t "b)"
