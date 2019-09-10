#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np
plt.title('Un primo plot con Python')
plt.xlabel('Tc')
plt.ylabel('Tf')
x, y = np.loadtxt('temp.dat', unpack=True)
plt.plot(x,y, 'x',label='Loaded from file!')
plt.xlim((-10,50))
plt.ylim((10,125))
plt.show()
