set terminal png enhanced size 1000, 1200
set output "temperatur_grid.png"
set hidden3d
set pm3d
set palette

set key left font ",16"

set multiplot layout 3, 2
set view 120, 140

set datafile missing "0.000000"

set xlabel "Dybde [m]" offset 0, -1
set ylabel "Tid [dager]" offset 0, -1
set zlabel "Temperatur [K]" rotate by 90 offset 1, 0

set xrange [0:1]
set yrange [0:10]
set zrange [264:276]
set cbrange [264:276]

set cbtics 4
set xtics 0.2 nomirror
set ytics 2 nomirror
set ztics 4 nomirror

set border 26

splot "results/high_1/temp.out" matrix u ($1/21.0):($2/10.0):3 with pm3d title "a)"
splot "results/high_05/temp.out" matrix u ($1/42.0):($2/10.0):3 with pm3d title "b)"
splot "results/middle_1/temp.out" matrix u ($1/21.0):($2/10.0):3 with pm3d title "c)"
splot "results/middle_05/temp.out" matrix u ($1/42.0):($2/10.0):3 with pm3d title "d)"
splot "results/low_1/temp.out" matrix u ($1/21.0):($2/10.0):3 with pm3d title "e)"
splot "results/low_05/temp.out" matrix u ($1/42.0):($2/10.0):3 with pm3d title "f)"
