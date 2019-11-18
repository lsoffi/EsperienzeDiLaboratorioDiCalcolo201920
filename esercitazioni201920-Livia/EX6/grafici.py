#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np
plt.title('Istogramma')
x, y = np.loadtxt('frequenzeDadi.dat', unpack=True)
plt.plot(x,y, 'x', label='dadi')
x, y = np.loadtxt('output_10.dat', unpack=True)
plt.plot(x,y, 'o', label='bernoulli')
plt.xlim((0,10))
plt.ylim((0,1))
plt.legend()
plt.savefig('fig.png')
plt.show()