set terminal png enhanced size 900, 600
set output "overflate.png"

set key right

set xtics nomirror
set ytics nomirror
set border 3

set xtics 2

set xlabel "Tid [dager]"
set ylabel "Varmestrøm [W/m²]"

plot "results/ultra_1/flux.out" u 1:(-$2) lw 2 lc "blue" w lines t "q_{sens}",\
    "results/ultra_1/flux.out" u 1:(-$3) lw 2 lc "red" w lines t "q_{lat}",\
    "results/ultra_1/flux.out" u 1:(-$4) lw 2 lc "green" w lines t "q_{kort}",\
    "results/ultra_1/flux.out" u 1:(-$5) lw 2 lc "orange" w lines t "q_{lang}"
