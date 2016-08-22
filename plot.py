import matplotlib.pyplot as pl
import numpy as np
a=[]
data = open("VxT.txt", "r+")

listOfData = data.readlines()

for i in xrange(len(listOfData)):
    a.append(listOfData[i].split())
xdata = []
ydata = []
for i in xrange(len(a)):
    ydata.append(a[i][0])
    xdata.append(a[i][1])


pl.scatter(xdata,ydata)
pl.show()
data.close()
