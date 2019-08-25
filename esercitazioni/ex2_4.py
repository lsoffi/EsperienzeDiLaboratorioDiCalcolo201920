#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np
plt.title('Un primo plot con Python')
plt.xlabel('x')
plt.ylabel('y')
x = np.linspace(0.0, 5.0, 10)
y = x
#list of tuples with two elements (i.e. x and y coordinates)
xy=zip(x,y)
# le unità di misura delle frecce sono le stesse del plot
# arrow(x,y,dx,dy) disegna una freccia da (x,y) a (x+dx,y+dy)
for p in xy:
    (xi, yi) = p
    plt.arrow(xi,yi,0,10.0,width=0.01,head_width=0.1, head_length=3.2, fc='r', ec='r')
plt.plot(x,y,label='y=x')
#ec=colore del bordo fc=colore di riempimento (e.g. r=red b=blue etc.)
x, y = np.loadtxt('temp.dat', usecols=(0,2), delimiter=' ', unpack=True)
plt.plot(x,y, 'x',label='Loaded from file!')
plt.savefig('traiettoria.png')
#plt.clf()
plt.show()
