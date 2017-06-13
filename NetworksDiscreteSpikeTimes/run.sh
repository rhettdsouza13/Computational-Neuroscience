truncate -s 0 VxT.txt
truncate -s 0 weightdist.txt
truncate -s 0 spikedist.txt

g++ RunNetwork.cpp -o fire_away

./fire_away 90
python plot.py 90
