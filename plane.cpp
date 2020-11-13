#include "plane.h"

Plane::Plane(int rows, vector<int> structure)
{
    int structure_size = structure.size();

    int **plane = init_matrix(rows, structure_size);
    int **original = init_matrix(rows, structure_size);

    for(int i = 0; i < rows; i++){
        for (int j = 0; j < structure_size; j++){
            if(i == 0){
                plane[i][j] == HALL;
                original[i][j] == HALL;
            }else{
                plane[i][j] = structure.at(j);
                original[i][j] = structure.at(j);
            }
        }     
    }

    this->plane = plane;
    this->original = original;
    this->rows = rows;
    this->cols = structure_size;
    this->structure = structure;
    this->hall = get_hall();
}

void Plane::print_plane(){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << plane[i][j] << " ";
        }
        cout << "\n";
    }
}

void Plane::print_original(){
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            cout << original[i][j] << " ";
        }
        cout << "\n";
    }
}

bool Plane::entrance_clear(){
    return plane[0][hall] == HALL;
}

int Plane::get_hall(){
    for(int i = 0; i < structure.size(); i++){
        if (structure.at(i) == HALL){
            return i;
        }
    }return 0;
}

vector<int> Plane::row_clear(int row, int col){
    vector<int> persons;

    int direction = (col > hall) ? 1 : -1;
    for(int i = hall + direction; i != col; i += direction){
        if(plane[row][i] == PERSON_SEAT)
            persons.push_back(i);
    }
    return persons;

}