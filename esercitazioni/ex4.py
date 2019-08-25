#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np
plt.title('Un primo plot con Python')
plt.xlabel('x')
plt.ylabel('y')
x = np.linspace(0.0, 5.0, 100)
y = x
plt.plot(x,y,label='y=x')
n_bins=100
x, y = np.loadtxt('temp.dat', usecols=(0,2), delimiter=' ', unpack=True)

fig, axs = plt.subplots(1, 2, sharey=True, tight_layout=True)

# We can set the number of bins with the `bins` kwarg
axs[0].hist(x, bins=n_bins)
axs[1].hist(y, bins=n_bins)

plt.plot(x,y, 'x',label='Loaded from file!')
plt.savefig('traiettoria.png')
#plt.clf()
plt.show()
