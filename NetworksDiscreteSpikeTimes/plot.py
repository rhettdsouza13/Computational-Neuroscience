import matplotlib.pyplot as pl
import numpy as np
import sys

syncProb = sys.argv[1]
binSize = 0.2
first=[]
second=[]
third=[]
data = open("VxT.txt", "r+")
weightData = open("weightdist.txt", "r+")
spikedata = open("spikedist.txt", "r+")
syncdata = open("syncdist3.txt", "a")

listOfWeightData = weightData.readlines()
listOfData = data.readlines()
listOfSpikeData = spikedata.readlines()

numberToAnalyze=(len(listOfData)-1)/(int(listOfData[0]))
numOfSyn =(len(listOfWeightData))/(int(listOfData[0]))


dataTuples=[[0,[],[]] for i in xrange(numberToAnalyze)]
dataWeightTuples=[[0,0,[],[]] for i in xrange(numOfSyn)]

dataSpikeTuples = [[],[]]
dataCount = [[],[]]
binPlot=[[],[]]
counter=0

for x in listOfSpikeData:
    if len(x.split())<2:
        continue
    dataSpikeTuples[0].append(x.split()[1])
    dataSpikeTuples[1].append(x.split()[0])


per=binSize
binNum=0
while per-binSize < float(dataSpikeTuples[0][len(dataSpikeTuples[0])-1]):
    dataCount[0].append(0)
    dataCount[1].append(binNum)
    binPlot[1].append(binNum)

    for t in dataSpikeTuples[0]:
        if float(t)>per or float(t)<per-binSize:
            continue
        else:
            dataCount[0][binNum]+=1

    if dataCount[0][binNum]>80:
        binPlot[0].append(1)
    else:
        binPlot[0].append(0)

    per+=binSize
    binNum+=1

syncs = 0

for i in xrange(len(binPlot[0])/4, (len(binPlot[0])-1)):
    syncs+=binPlot[0][i]
syncdata.write(str(syncs) + " " + str(syncProb) + "\n")




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


# pl.figure(1).canvas.set_window_title("Altogether")
# for lines in dataTuples:
#     line, = pl.plot(lines[1],lines[2], label=str(lines[0]))
#     legendHandles.append(line)
# pl.legend(handles = legendHandles)
#
# legendWeightHandles=[]
#
# pl.figure(2).canvas.set_window_title("WeightsCurve")
# for lines in dataWeightTuples:
#     labeller = str(lines[0]) + " -- " + str(lines[1])
#     line, = pl.plot(lines[2],lines[3], label=labeller)
#     legendWeightHandles.append(line)
# pl.legend(handles = legendWeightHandles)


pl.figure(1).canvas.set_window_title("Spike Distribution")
pl.scatter(dataSpikeTuples[0],dataSpikeTuples[1])

pl.figure(2).canvas.set_window_title("Spike Count Distribution")
pl.plot(dataCount[1],dataCount[0])

pl.figure(3).canvas.set_window_title("Binary Spike Count Distribution")
pl.plot(binPlot[1],binPlot[0])

pl.show()

data.close()
spikedata.close()
weightData.close()
syncdata.close()
