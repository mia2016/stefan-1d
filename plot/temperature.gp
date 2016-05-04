set term wxt
#set terminal png enhanced size 1000, 800
#set output "temperature.png"
set hidden3d
set pm3d
set palette

set view 120, 140

set datafile missing "0.000000"

set xlabel "Posisjon [m]"
set ylabel "Tid [dager]"
set zlabel "Temperatur [K]" rotate by 90
set key off

#set xrange [0:1]
#set yrange [0:9]
#set zrange [265:274]

#set xtics nomirror
#set ytics nomirror
#set ztics nomirror

#set border 26

splot "temp.out" matrix u ($1/21.0):($2/10.0):3 with pm3d 
