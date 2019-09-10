#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import (MultipleLocator,FormatStrFormatter)
import matplotlib.font_manager as font_manager
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
plt.plot(x,y, 'b-',label='istogramma')
font_prop = font_manager.FontProperties(size=18)
plt.savefig('istogramma.png')
plt.show()
