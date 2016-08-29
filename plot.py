import matplotlib.pyplot as pl
import numpy as np
first=[]
second=[]
third=[]
data = open("VxT.txt", "r+")

listOfData = data.readlines()
i=0
while(i<len(listOfData)):
    first.append(listOfData[i].split())
    second.append(listOfData[i+1].split())
    third.append(listOfData[i+2].split())
    i+=3
x1data = []
y1data = []
x2data = []
y2data = []
x3data = []
y3data = []

for j in xrange(len(first)):
    y1data.append(first[j][0])
    x1data.append(first[j][1])
for j in xrange(len(second)):
    y2data.append(second[j][0])
    x2data.append(second[j][1])
for j in xrange(len(third)):
    y3data.append(third[j][0])
    x3data.append(third[j][1])


line1, = pl.plot(x1data,y1data, label = "First")
line2, = pl.plot(x2data,y2data, label= "Second")
line3, = pl.plot(x3data,y3data, label = "Third")
pl.legend(handles = [line1,line2,line3])
pl.show()
data.close()
