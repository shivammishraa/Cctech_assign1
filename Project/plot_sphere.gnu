set terminal wxt
set parametric
set hidden3d
set mouse
set urange [0:2*pi]
set vrange [0:pi]
set xlabel 'X'
set ylabel 'Y'
set zlabel 'Z'
set view equal xyz
r = 5
splot 'data/transformed_sphere.dat' with points pointtype 7 linecolor 'blue'
