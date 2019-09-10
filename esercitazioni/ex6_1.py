#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import (MultipleLocator, FormatStrFormatter)
import matplotlib.font_manager as font_manager
fontp={'size':'18', 'color': 'blue'}
plt.title('Distribuzione Binomiale',**fontp)
ax = plt.gca()
ax.xaxis.set_major_formatter(FormatStrFormatter('%.0f'))
ax.yaxis.set_minor_locator(MultipleLocator(0.01))
ax.xaxis.set_major_locator(MultipleLocator(2))
ax.xaxis.set_minor_locator(MultipleLocator(1))
plt.xlabel('k',**fontp)
plt.ylabel('P(k)',**fontp)
x, y = np.loadtxt('bernoulli_20.dat', unpack=True)
plt.plot(x,y, 'b-',label='bernoulli')
font_prop = font_manager.FontProperties(size=18)
plt.savefig('bernoulli_20.png')
plt.show()
