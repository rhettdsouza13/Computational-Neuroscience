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

x_sm = np.array(xdata)
y_sm = np.array(ydata)

x_smooth = np.linspace(x_sm.min(), x_sm.max())
y_smooth = spline(x, y, x_smooth)

pl.plot(x_smooth,y_smooth)
pl.show()
data.close()
