#/bin/bash
#
cd libSplines/ && mkdir build && cd build
cmake ../ -DBUILD_SHARED_LIBS=0 && make install
#cmake ../ -DBUILD_SHARED_LIBS=1 && make install
#
cd ../../ && mkdir build && cd build
cmake ../ -DDYNAMIC_LINK_TYPE=0 && make install
#cmake ../ -DDYNAMIC_LINK_TYPE=1 && make install
cd ../bin
#
./spline akima > akima.txt
#LD_LIBRARY_PATH=../libSplines/lib/ ./spline > akima.txt
./spline cubic > cubic.txt
#LD_LIBRARY_PATH=../libSplines/lib/ ./spline > cubic.txt
./spline points > points.txt
#LD_LIBRARY_PATH=../libSplines/lib/ ./spline > points.txt
python plot.py points.txt akima.txt cubic.txt