set terminal png enhanced size 1000, 1000
set output "grense.png"


set multiplot layout 3, 2

set xtics 200


set key off


set ylabel "Tykkelse [m]"
plot "log.out" u 0:37 w lines title "Istykkelse", "log.out" u 0:40 w lines title "Snøtykkelse"

unset ylabel
plot "log.out" u 0:37 w lines title "Istykkelse", "log.out" u 0:40 w lines title "Snøtykkelse"

set ylabel "Tykkelse [m]"
plot "log.out" u 0:37 w lines title "Istykkelse", "log.out" u 0:40 w lines title "Snøtykkelse"

unset ylabel
plot "log.out" u 0:37 w lines title "Istykkelse", "log.out" u 0:40 w lines title "Snøtykkelse"

set xlabel "Timer"
set ylabel "Tykkelse [m]"
plot "log.out" u 0:37 w lines title "Istykkelse", "log.out" u 0:40 w lines title "Snøtykkelse"

unset ylabel
plot "log.out" u 0:37 w lines title "Istykkelse", "log.out" u 0:40 w lines title "Snøtykkelse"
