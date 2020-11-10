#ifndef PERSON_H
#define PERSON_H

#include <iostream>

using namespace std;

class Person {
public:
    int startx, starty, goalx, goaly;

    Person(int startx, int starty, int goalx, int goaly);

    void print_person();

};

#endif