#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np
plt.title('Un primo plot con Python')
plt.xlabel('x')
plt.ylabel('y')
x = np.linspace(-10.0, 50.0, 100)
#y = x
conv = 5.0/9.0
offset = 32.0
y=x/conv + offset
plt.plot(x,y,label='retta interpolante')
x, y = np.loadtxt('temp.dat', unpack=True)
plt.plot(x,y, 'x',label='temp.dat')
#ottiene gli estremi attuali
#left, right = plt.xlim()  
plt.xlim(left=0)
plt.xlim(right=50.0)
plt.show()
