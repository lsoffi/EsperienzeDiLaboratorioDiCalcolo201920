#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np

plt.title('Traiettoria')
plt.xlabel('x')
plt.ylabel('y')
x, y = np.loadtxt('temp.dat', comments=['#'], usecols=(1,2), unpack=True)
plt.plot(x, y, 'x',label='Traiettoria')
plt.savefig('traiettoria.png')
plt.show()

# facciamo un reset della figura
plt.clf()

plt.title('x in funzione del tempo')
plt.xlabel('t')
plt.ylabel('x')
t, x = np.loadtxt('temp.dat', comments=['#'], usecols=(0,1), unpack=True)
plt.plot(t, x, 'x',label='x in funzione del tempo')
plt.savefig('x.png')
plt.show()

# un altro reset della figura
plt.clf()

plt.title('y in funzione del tempo')
plt.xlabel('t')
plt.ylabel('y')
t, y = np.loadtxt('temp.dat', comments=['#'], usecols=(0,2), unpack=True)
plt.plot(t, y, 'x',label='y in funzione del tempo')
plt.savefig('y.png')
plt.show()
