#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import (MultipleLocator, FormatStrFormatter)
fontp={'size':'18', 'color': 'blue'}
plt.title('Istogramma',**fontp)
ax = plt.gca()
ax.xaxis.set_major_formatter(FormatStrFormatter('%.0f'))
ax.yaxis.set_minor_locator(MultipleLocator(0.01))
ax.xaxis.set_major_locator(MultipleLocator(2))
ax.xaxis.set_minor_locator(MultipleLocator(1))
plt.xlabel('k',**fontp)
plt.ylabel('P(k)',**fontp)
x, y = np.loadtxt('istogramma.dat', unpack=True)
plt.plot(x,y, 'bx-',label='istogramma')
x, y = np.loadtxt('bernoulli_20.dat', unpack=True)
plt.plot(x,y, 'ro-',label='bernoulli')
ax.legend();
plt.savefig('isto_bern.png')
plt.show()
