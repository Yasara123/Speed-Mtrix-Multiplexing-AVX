****sequential program****

compile: g++ -fopenmp -o serial.out serial.cpp
run: ./serial.out <matrix size>

****parallel program****

compile: g++ -fopenmp -o parallel.out parallel.cpp
run: ./parallel.out <matrix size>

****optimized parallel program****

compile: g++ -mavx -std=c++11 -fopenmp -O3 optimized.cpp -o optimized
run: ./optimized <matrix size>
