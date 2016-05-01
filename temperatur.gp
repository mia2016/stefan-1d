set term wxt
#set output "temperature.png"
set pm3d
set palette

set xlabel "Posisjon"
set ylabel "Iterasjon"
set zlabel "Temperatur"
set key off

splot "temp.out" matrix  with lines
#splot "temp.out" matrix with lines
#splot for [i=1:10] "log.out" using i:0:(column(i)) with linespoint
#splot for [i=1:10] "log.out" using i:
