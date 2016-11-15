import random

numOfNodes = input("Enter Num Of Nodes -> ")

outFile = open("network.txt", "wb+")
outFile.write(str(numOfNodes) + "\n")
for i in xrange(numOfNodes):
    for j in range(i+1,numOfNodes):
        if random.randrange(0,10) > 5:
            toWrite = str(i) + " " + str(j) + " " + str(random.uniform(0,50)) + "\n"
            outFile.write(toWrite)
