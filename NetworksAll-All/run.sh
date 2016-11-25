truncate -s 0 VxT.txt
truncate -s 0 weightdist.txt
truncate -s 0 spikedist.txt

g++ RunNetwork.cpp -o fire_away

./fire_away
python plot.py
truncate -s 0 filename
