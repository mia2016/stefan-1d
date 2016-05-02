set terminal png enhanced size 1000, 1000
set output "temperatur_grid.png"
set hidden3d
set pm3d
set palette

set view 110, 150

set datafile missing "0.000000"
set multiplot layout 3, 2

set key off

splot "temp.out" matrix with lines
splot "temp.out" matrix with lines
splot "temp.out" matrix with lines
splot "temp.out" matrix with lines
splot "temp.out" matrix with lines
splot "temp.out" matrix with lines
