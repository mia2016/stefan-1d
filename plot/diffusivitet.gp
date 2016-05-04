set terminal png enhanced size 800, 400
set output "diffusivitet.png"

set ylabel "Termisk diffusivitet [m²/s]"
set xlabel "Temperatur [K]"

unset key

set xrange [250:273]

set ytics nomirror
set xtics nomirror

set border 3

k(x) = 1.16*(1.91-(x-273)*8.66*10**(-3)+(x-273)**2*2.97*10**(-5))
c(x) = 185+6.89*x
p(x) = 917*(1-(x-273.15)*1.17*10**(-4))

print k(270.15)
print c(270.15)
print p(270.15)
print k(270.15)/(c(270.15)*p(270.15))

plot k(x)/(c(x)*p(x)) lc "blue" lw 2 with lines
