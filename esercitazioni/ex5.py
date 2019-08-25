#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np
plt.title('Esercizio 5')
plt.xlabel('trimestri')
plt.ylabel('medie orarie')
#ogni colonna è un commesso (in tutto sono 10)
for cc in range(0,3):
    y = np.loadtxt('dati.dat', usecols=(cc), delimiter=' ', unpack=True)
    plt.plot(y, label='venditore #'+str(cc+1))
plt.legend()    
plt.savefig('isto1.png')
plt.xticks(np.arange(4),('T1','T2','T3', 'T4'))
plt.show()
