set terminal png enhanced size 1000, 1000
set output "temperatur_grid.png"

set multiplot layout 3, 2

set key off

set ylabel "Temperatur [K]"
plot "temp2.out" with lines

unset ylabel
plot "temp2.out" with lines

set ylabel "Temperatur [K]"
plot "temp2.out" with lines

unset ylabel
plot "temp2.out" with lines

set xlabel "Posisjon [m]"
set ylabel "Temperatur [K]"
plot "temp2.out" with lines

unset ylabel
plot "temp2.out" with lines
