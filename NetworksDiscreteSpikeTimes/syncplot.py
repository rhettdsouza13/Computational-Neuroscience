import matplotlib.pyplot as pl
import numpy as np

sync1 = open('syncdist.txt', 'r')
sync2 = open('syncdist2.txt', 'r')


data1pl = [data.split() for data in sync1.readlines()]
data2pl = [data.split() for data in sync2.readlines()]

plotx=[]
ploty=[]

for val1, val2 in zip(data1pl,data2pl):
    ploty.append((float(val1[0])+float(val2[0]))/2)
    plotx.append(int(val1[1]))

print ploty

pl.plot(plotx, ploty)
pl.show()
