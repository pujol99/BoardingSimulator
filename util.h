#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <thread>
#include <chrono>
#include <stdlib.h>

using namespace std;

int** init_matrix(int rows, int cols);
void sleep(int ms);
void copy(int** from, int** to, int rows, int cols);

#endif