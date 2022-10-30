#!/bin/sh
g++ test_matrix_functions.cpp matrix_functions.cpp -o test -fopenmp -lgtest -lgmock -pthread 
./test
