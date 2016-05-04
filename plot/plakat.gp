#set term wxt
set terminal png enhanced size 600, 800
set output "plakat.png"
set hidden3d
set pm3d
set palette

set key left font ",20"
set multiplot layout 2, 1

set view 120, 140

set datafile missing "0.000000"

set xlabel "Posisjon [m]" offset 0, -0.7
set ylabel "Tid [dager]" offset 0, -0.5
set zlabel "Temperatur [K]" rotate by 90 offset 1

set xrange [0:1]
set yrange [0:10]
set zrange [264:274]
set cbrange [264:274]

set cbtics 3 
set xtics 0.2 nomirror
set ytics 2 nomirror offset -0.2, -0.4
set ztics 3 nomirror

set border 26

splot "results/high_1/temp.out" matrix u ($1/21.0):($2/10.0):3 with pm3d t "a)"
splot "results/low_1/temp.out" matrix u ($1/21.0):($2/10.0):3 with pm3d t "b)"
