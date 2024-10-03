mkdir build
cd build

cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
cd ..
./build/analyse && gnuplot plt
