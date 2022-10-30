#!/bin/sh
sudo apt install g++
sudo apt install libomp-dev
g++ main.cpp matrix_functions.cpp -fopenmp -o main
./main
