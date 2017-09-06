outputname = "search.pdf"
set terminal postscript eps color enhanced  font 'Verdana,14' size 8cm,6cm
set output '| epstopdf --filter --outfile='.outputname
set style line 1 lt 1 lw 3.5 lc rgb "#25578F" pt 7 ps 1
set style line 2 lt 1 lw 3.5 lc rgb "#D11F29" pt 2 ps 1
set style line 3 lt 1 lw 3.5 lc rgb "#499943" pt 5 ps 1
set style line 4 lt 1 lw 3.5 lc rgb "#F39F2C" pt 5 ps 1
set style line 5 lt 1 lw 3.5 lc rgb "#4B0082" pt 5 ps 1
set style line 11 lt 1 lw 3.5 lc rgb '#444444' 
set style line 12 lt 2 lw 3.5 lc rgb '#444444' 
set border 3 back ls 11
set tics nomirror
set arrow from graph 1,0 to graph 1.02,0 size screen 0.025,15,60 filled ls 11
set arrow from graph 0,1 to graph 0,1.05 size screen 0.025,15,60 filled ls 11
set key top left
set title "Heuristic"
set xlabel "# states"
set ylabel "heuristic"
plot "-"  title "heuristic" with lines ls 1, "-" title "min heuristic" with lines ls 2
0 5
1 4
2 4
5 3
6 2
7 2
8 2
9 2
10 1
11 0
e
0 5
1 4
2 4
5 3
6 2
7 2
8 2
9 2
10 1
11 0
e
