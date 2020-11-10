#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include "util.h"

using namespace std;

class Plane {
public:
    int **plane;
    int rows, cols;

    Plane(int rows, int structure[], int structure_size);

    void print_plane();
};

#endif