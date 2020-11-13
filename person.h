#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include "plane.h"

using namespace std;

enum _state {OUTSIDE, WALKING, SEATED, LEAVING, RETURNING};

class Person {
public:
    int x, y, goalx, goaly;
    _state state;

    Person(int x, int y, int goalx, int goaly);

    void print_person();
    void in_goal();
    void move_hall(int hall);
    void move_forwards();
    void move_sideways();
    void enter_plane(int hall);

};

#endif