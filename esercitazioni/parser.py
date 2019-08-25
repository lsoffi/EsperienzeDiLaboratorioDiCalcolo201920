#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jun 18 09:59:18 2019

@author: demichel
"""
import os, sys,re
import numpy as np

txt='arctan(x)+x'
t2=re.sub('(?!<np\.)arctan','np.arctan', txt)
print('t2=',t2)
txt='x**2+1'
#quit()
#xa=np.linspace(0,5,10)
#ypa=[]
#for x in xa:
#    ypa.append(eval(txt))
#ya=np.array(ypa)
#print('ya=',ya)
#plt.plot(xa,ya)