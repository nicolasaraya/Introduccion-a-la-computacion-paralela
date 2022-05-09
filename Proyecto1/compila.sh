clear
echo '----Algoritmo 1----'

g++ alg.cpp -std=c++11 -march=native -fopenmp -O3 -lm 
./a.out 1 1000000
./a.out 2 1000000
./a.out 4 1000000
./a.out 6 1000000
./a.out 8 1000000
./a.out 10 1000000
./a.out 12 1000000

echo ' '
echo '----Algoritmo 2----'

g++ alg-2.cpp -std=c++11 -march=native -fopenmp -O3 -lm 
./a.out 1 1000000
./a.out 2 1000000
./a.out 4 1000000
./a.out 6 1000000
./a.out 8 1000000
./a.out 10 1000000
./a.out 12 1000000
