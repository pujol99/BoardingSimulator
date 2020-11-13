#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <vector>
#include "util.h"

using namespace std;

enum _type {HALL, SEAT, PERSON, PERSON_SEAT};

class Plane {
public:
    int **plane;
    int **original;

    int rows, cols, hall;
    vector<int> structure;
    _type type;

    Plane(int rows, vector<int> structure);

    void print_plane();
    void print_original();
    int get_hall();
    bool entrance_clear();
    vector<int> row_clear(int row, int col);
};

#endif