set terminal png enhanced size 800, 300
set output "varme.png"

set key right

set xtics nomirror
set ytics nomirror
set border 3

set xtics 2

set xlabel "Tid [dager]"
set ylabel "Varmestrøm [W/m²]"

plot "results/ultra_1/flux.out" u 1:(-$6) lw 2 lc "blue" w lines t "q_{overflate}",\
    "results/ultra_1/flux.out" u 1:($7) lw 2 lc "red" w lines t "q_{frys}",\
    "results/ultra_1/flux.out" u 1:(-$8) lw 2 lc "green" w lines t "q_{snø/is}",\
    "results/ultra_1/flux.out" u 1:(-$9) lw 2 lc "orange" w lines t "q_{kjøling}"
