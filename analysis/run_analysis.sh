mkdir build
cd build
cmake ..
make
cd ..
./build/analyse && gnuplot plt
