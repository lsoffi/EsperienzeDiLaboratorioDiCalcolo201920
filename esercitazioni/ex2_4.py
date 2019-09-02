#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np
plt.title('Esercizio N. 2 - frecce in python')
plt.xlabel('x')
plt.ylabel('y')
#list of tuples with two elements (i.e. x and y coordinates)
x, y, vx, vy = np.loadtxt('temp.dat', usecols=(0,1,2,3), unpack=True)
# le unità di misura delle frecce sono le stesse del plot
# arrow(x,y,dx,dy) disegna una freccia da (x,y) a (x+dx,y+dy)
for cc in range(0,len(x)):
    xi=x[cc]
    yi=y[cc]
    vxi=vx[cc]
    vyi=vy[cc]
    print ('cc='+str(cc))
    plt.arrow(xi,yi,5*vxi,5*vyi,width=0.2,head_width=0.5,head_length=0.3, fc='r', ec='r')
plt.plot(x,y,label='traiettora con velocità')
#ec=colore del bordo fc=colore di riempimento (e.g. r=red b=blue etc.)
#plt.plot(x,y, 'x',label='Loaded from file!')
plt.savefig('traiettoria.png')
#plt.clf()
plt.show()
