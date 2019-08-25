#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jun 18 08:21:34 2019

@author: demichel
"""
#import os,sys

import numpy as np
import matplotlib.pyplot as plt
import wx
class ExamplePanel(wx.Panel):
    def __init__(self, parent):
        self.text=''
        self.ivar='x'
        self.xmin=0
        self.xmax=5.0
        self.np=100
        wx.Panel.__init__(self, parent)
        self.quote = wx.StaticText(self, label="function to plot", pos=(10, 25))
        # A multiline TextCtrl  - expressione da valutare
        self.edit = wx.TextCtrl(self, pos=(10,50), size=(350,100), style=wx.TE_MULTILINE)
        self.Bind(wx.EVT_TEXT, self.EvtText, self.edit)
        alt=30
        lar=60
        xpos=20
        ypos=180
        yposlbl=ypos-20
        # TextCtrl - variabile indipendente
        wx.StaticText(self, label="indip. var.", pos=(xpos, yposlbl))
        self.txtindipvar = wx.TextCtrl(self, pos=(xpos,180), size=(lar,alt))
        self.Bind(wx.EVT_TEXT, self.EvtTextIV, self.txtindipvar)
        self.txtindipvar.AppendText('x')
        
        # TextCtrl - xmin
        xpos+=lar+5
        wx.StaticText(self, label="x min", pos=(xpos, yposlbl))
        self.txtxmin = wx.TextCtrl(self, pos=(xpos,ypos), size=(lar,alt))
        self.Bind(wx.EVT_TEXT, self.EvtTextxmin, self.txtxmin)
        self.txtxmin.AppendText(str(self.xmin))
        
        # TextCtrl - xmax
        xpos+=lar+5
        wx.StaticText(self, label="x max", pos=(xpos, yposlbl))
        self.txtxmax = wx.TextCtrl(self, pos=(xpos,ypos), size=(lar,alt))
        self.Bind(wx.EVT_TEXT, self.EvtTextxmax, self.txtxmax)
        self.txtxmax.AppendText(str(self.xmax))
        
        # TextCtrl - npoints
        xpos+=lar+5
        wx.StaticText(self, label="# points", pos=(xpos, yposlbl))
        self.txtnpoints = wx.TextCtrl(self, pos=(xpos,ypos), size=(lar,alt))
        self.Bind(wx.EVT_TEXT, self.EvtTextnpoints, self.txtnpoints)
        self.txtnpoints.AppendText(str(self.np))
        
        # A button
        xpos += lar+10
        self.button =wx.Button(self, label="Plot", pos=(xpos, ypos))
        self.Bind(wx.EVT_BUTTON, self.OnClick,self.button)
    def parse(self,txt):
        npfuncs=['arcsinh', 'arccosh', 'arctanh', 'arcsin', 'arccos', 'arctan','arctan2', 'sinh', 'cosh', 
                 'tanh', 'sin', 'cos', 'tan', 'exp', 'log', 'log10', 'sqrt']
        for a in npfuncs:
            replU='_'+('np.'+a).upper()+'_'    
            txt=txt.replace(a,replU)
        for a in npfuncs:
            replU='_'+('np.'+a).upper()+'_'
            replL=('np.'+a).lower()
            txt=txt.replace(replU,replL)    
        return txt
    def OnClick(self,event):
        xa=np.linspace(self.xmin,self.xmax,self.np)
        ypa=[]
        txt = self.parse(self.text)
        if txt=='':
            return
        #replace indipendent variable if != 'x'
        iv=self.ivar
        #print('ivar=', iv)
        for x in xa:
            try:
                exec("%s = %.15G" % (iv,x))
                ypa.append(eval(txt))
            except SyntaxError:
                print('Parse error in expressio...')
                pass
            ya=np.array(ypa)
        plt.plot(xa,ya)    
        plt.show()
    def EvtText(self, event):
        self.text=event.GetString()
    def EvtTextxmax(self, event):
        try:
            self.xmax=float(event.GetString())
        except ValueError:
            pass
    def EvtTextxmin(self, event):
        try:
            self.xmin=float(event.GetString())
        except ValueError:
            pass
    def EvtTextnpoints(self, event):
        try:
            self.np=int(event.GetString())
        except ValueError:
            pass
    def EvtTextIV(self, event):
        self.ivar=event.GetString()
app = wx.App(False)
frame = wx.Frame(None)#MainWindow(None, "Sample editor")
panel = ExamplePanel(frame)
frame.Show()
app.MainLoop()
