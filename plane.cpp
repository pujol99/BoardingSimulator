#include "plane.h"

Plane::Plane(){
    rows = 10;
    cols = 10;
}

void Plane::printPlane(){
    cout << "Plane with " << rows << " rows and ";
    cout << cols << " cols" << endl;
}