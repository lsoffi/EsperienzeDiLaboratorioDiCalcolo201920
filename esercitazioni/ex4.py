#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np
plt.title('Esercizio 4')
plt.xlabel('x')
plt.ylabel('y')
n_bins=36
x, y = np.loadtxt('dati.dat', usecols=(0,1), delimiter=' ', unpack=True)
plt.bar(x,y,fill=True)
plt.savefig('isto1.png')
#plt.clf()
plt.show()
