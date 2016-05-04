set terminal png enhanced size 900, 800
set output "vaer.png"


set multiplot layout 2, 1

set key right

set yrange [0:13]
set y2range [0:13]

set xtics 2 
set y2tics


set xlabel "Tid [dager]"

set ylabel "Vindhastighet [m/m²]"
set y2label "Temperatur [C]"

plot "data.csv" u ($0/25):1 lw 2 lc "blue" w lines t "Vindhastighet" axes x1y1,\
    "data.csv" u ($0/25):2 lw 2 lc "red" w lines t "Temperatur" axes x1y1

set yrange [0:1.2]
set y2range [0:1.2]

set ylabel "Relativ fuktighet"
set y2label "Skydekke"

plot "data.csv" u ($0/25):3 lw 2 lc "green" w lines t "Relativ fuktighet" axes x1y2,\
    "data.csv" u ($0/25):4 lw 2 lc "orange" w lines t "Skydekke" axes x1y2
