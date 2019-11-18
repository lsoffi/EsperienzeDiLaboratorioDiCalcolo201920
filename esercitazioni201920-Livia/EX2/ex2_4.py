#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np

plt.title('Esercizio N. 2 - frecce in python')
plt.xlabel('x')
plt.ylabel('y')

x, y, vx, vy = np.loadtxt('temp.dat', usecols=(0,1,2,3), unpack=True)

# le unità di misura delle frecce sono le stesse del plot
# arrow(x,y,dx,dy) disegna una freccia da (x,y) a (x+dx,y+dy)
# anche width, head_width, etc. sono in unità di misura del plot
# di conseguenza se gli assi hanno unità differenti le frecce risultano "deformate"
for cc in range(0, len(x)):
    xi = x[cc]
    yi = y[cc]
    vxi = vx[cc]
    vyi = vy[cc]
    plt.arrow(xi, yi, 20*vxi, 20*vyi, width=0.05, head_width=0.4, head_length=0.4, fc='r', ec='r')

# impostiamo le stesse unità di misura per gli assi x e y per non deformare le frecce (gca è un acronimo per "get current axes")
ax=plt.gca().set_aspect('equal')
plt.plot(x, y, label='traiettora con velocità')
plt.savefig('traiettoria.png')
plt.show()
