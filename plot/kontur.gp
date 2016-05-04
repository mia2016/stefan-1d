#set term wxt
set terminal png enhanced size 1000, 1000
set output "kontur.png"

set ylabel "Tid [dager]" offset 0, 5
set xlabel "Dybde [m]" offset 5, 0
set cblabel "Temperature [K]" offset -12, 0

set parametric
set datafile missing "0.000000"
#set view map
set view 180, 90, 1
#set contour base
#set cntrparam levels 5
unset key
unset ztics

#set xrange [0:10]
#set yrange [0:1]

set xtics nomirror
set ytics nomirror
set cbtics 1

set border 26

splot "temp.out" matrix u ($1/201.0):($2/10.0):3 with pm3d
