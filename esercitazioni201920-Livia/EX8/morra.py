import matplotlib.pyplot as plt
import numpy as np


plt.figure(1)
plt.title('Esercizio 8')
plt.xlabel('numero getti')
plt.ylabel('punteggi')
tempo,punteggioA,punteggioB= np.loadtxt('punteggio.dat', usecols=(0,1,2) ,comments=['#'], unpack=True)
plt.plot(tempo,punteggioA,'-o',color='red',label='GIOCATORE A')
plt.plot(tempo,punteggioB,'-x',color='green',label='GIOCATORE B')
plt.legend()
plt.xlim(-0.5, 9.5);
plt.ylim(-0.5, 5.5);
plt.savefig('PunteggiMorraCinese.png')    
plt.show()