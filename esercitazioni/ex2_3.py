#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np
plt.title('Un primo plot con Python')
plt.xlabel('x')
plt.ylabel('y')
x = np.linspace(0.0, 5.0, 100)
y = x
plt.plot(x,y,label='y=x')
x, y = np.loadtxt('temp.dat', comments=['#'], usecols=(0,2), delimiter=' ', unpack=True)
plt.plot(x,y, 'x',label='Loaded from file!')
plt.savefig('traiettoria.png')
#plt.clf()
plt.show()
