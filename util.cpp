#include "util.h"

int** init_matrix(int rows, int cols){
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; ++i)
        matrix[i] = new int[cols];
    return matrix;
}

void sleep(int ms){
    this_thread::sleep_for(chrono::milliseconds(ms));
    system("clear");
}

void copy(int** from, int** to, int rows, int cols){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            to[i][j] = from[i][j];
        }
    }
}

void read_configuration(int &rows, vector<int> &structure, int &speed){
    char data[100];
    int cols;

    ifstream config("configuration.txt");

    config >> data; 
    speed = atoi(data);

    config >> data; 
    rows = atoi(data);

    config >> data; 
    cols = atoi(data);

    config >> data;
    for(int i = 0; i < cols; i++){
        cout << (int)data[i] << endl;
        structure.push_back((int)data[i]-48);
    }

    config.close();
}