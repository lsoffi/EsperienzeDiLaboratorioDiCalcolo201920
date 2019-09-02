#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np
plt.title('Esercizio N. 2 - frecce in python')
plt.xlabel('x')
plt.ylabel('y')
#list of tuples with two elements (i.e. x and y coordinates)
x, y, vx, vy = np.loadtxt('temp.dat', usecols=(0,1,2,3), unpack=True)
arrows=zip(x,y,vx,vy)
# le unità di misura delle frecce sono le stesse del plot
# arrow(x,y,dx,dy) disegna una freccia da (x,y) a (x+dx,y+dy)
for p in arrows:
    xi=p[0]
    yi=p[1]
    vxi=p[2]
    vyi=p[3]
    plt.arrow(xi,yi,vxi,vyi,width=0.01,head_width=0.1, head_length=3.2, fc='r', ec='r')
plt.plot(x,y,label='traiettora con velocità')
#ec=colore del bordo fc=colore di riempimento (e.g. r=red b=blue etc.)
plt.plot(x,y, 'x',label='Loaded from file!')
plt.savefig('traiettoria.png')
#plt.clf()
plt.show()
