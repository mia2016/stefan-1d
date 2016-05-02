set term wxt
#set terminal png enhanced size 1920, 1080
#set output "temperature.png"
set hidden3d
#set pm3d
set palette

set view 110, 150

set datafile missing "0.000000"
set ztics 3

set xlabel "Posisjon [m]"
set ylabel "Dager"
set zlabel "Temperatur [K]"
set key off

splot "temp.out" matrix with lines
