#include "util.h"

int** init_matrix(int rows, int cols){
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i)
        matrix[i] = new int[cols];
    return matrix;
}

void sleep(int ms){
    this_thread::sleep_for(chrono::milliseconds(ms));
    //system("clear");
}