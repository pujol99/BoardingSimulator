#include "plane.h"

Plane::Plane(int rows, int structure[], int structure_size){
    int** matrix = init_matrix(rows*2, structure_size);

    for(int i = 0; i < rows*2; i++){
        for (int j = 0; j < structure_size; j++)
        {
            matrix[i][j] = (i%2==1) ? structure[j] : 0;
        }
    }

    this->plane = matrix;
    this->rows = rows*2;
    this->cols = structure_size;
}

void Plane::print_plane(){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << plane[i][j]<< " ";
        }
        cout << "\n";
    }
}