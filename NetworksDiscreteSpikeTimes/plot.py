import matplotlib.pyplot as pl
import numpy as np
first=[]
second=[]
third=[]
data = open("VxT.txt", "r+")
weightData = open("weightdist.txt", "r+")
spikedata = open("spikedist.txt", "r+")

listOfWeightData = weightData.readlines()
listOfData = data.readlines()
listOfSpikeData = spikedata.readlines()

numberToAnalyze=(len(listOfData)-1)/(int(listOfData[0]))
numOfSyn =(len(listOfWeightData))/(int(listOfData[0]))


dataTuples=[[0,[],[]] for i in xrange(numberToAnalyze)]
dataWeightTuples=[[0,0,[],[]] for i in xrange(numOfSyn)]

dataSpikeTuples = [[],[]]
counter=0

for x in listOfSpikeData:
    if len(x.split())<2:
        continue
    dataSpikeTuples[0].append(x.split()[1])
    dataSpikeTuples[1].append(x.split()[0])


i=1
while (i<len(listOfData)):
    for j in xrange(numberToAnalyze):
        dataTuples[j][0]=listOfData[i+j].split()[0]
        dataTuples[j][1].append(listOfData[i+j].split()[2])
        dataTuples[j][2].append(listOfData[i+j].split()[1])
    i+=numberToAnalyze

k=0


while (k<len(listOfWeightData)):
    for l in xrange(numOfSyn):
        dataWeightTuples[l][0] = listOfWeightData[k+l].split()[0]
        dataWeightTuples[l][1] = listOfWeightData[k+l].split()[1]
        dataWeightTuples[l][2].append(listOfWeightData[k+l].split()[3])
        dataWeightTuples[l][3].append(listOfWeightData[k+l].split()[2])

    k+=numOfSyn

legendHandles=[]


pl.figure(1).canvas.set_window_title("Altogether")
for lines in dataTuples:
    line, = pl.plot(lines[1],lines[2], label=str(lines[0]))
    legendHandles.append(line)
pl.legend(handles = legendHandles)

legendWeightHandles=[]

pl.figure(2).canvas.set_window_title("WeightsCurve")
for lines in dataWeightTuples:
    labeller = str(lines[0]) + " -- " + str(lines[1])
    line, = pl.plot(lines[2],lines[3], label=labeller)
    legendWeightHandles.append(line)
pl.legend(handles = legendWeightHandles)


pl.figure(3).canvas.set_window_title("Spike Distribution")
pl.scatter(dataSpikeTuples[0],dataSpikeTuples[1])


pl.show()
data.close()
spikedata.close()
weightData.close()
