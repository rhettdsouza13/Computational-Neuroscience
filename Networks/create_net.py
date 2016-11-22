import random

numOfNodes = input("Enter Num Of Nodes -> ")

net = [[0 for j in xrange(numOfNodes)] for i in xrange(numOfNodes)]

outFile = open("network.txt", "wb+")
outFile.write(str(numOfNodes) + "\n")
for i in xrange(numOfNodes):
    for j in xrange(numOfNodes):
        if random.randrange(0,100) > 75:
            if net[j][i]==0:
                toWrite = str(i) + " " + str(j) + " " + str(random.uniform(0,50)) + "\n"
                net[i][j]=1
                outFile.write(toWrite)
