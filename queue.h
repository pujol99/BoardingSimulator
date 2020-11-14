#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "plane.h"
#include "person.h"

using namespace std;

class Queue
{
public:
    vector<Person*> queue;

    Queue(Plane* plane);

    void print_queue();
    Person* get_person(int x, int y);
    vector<Person*> get_persons(int x, int y);
    bool all_seated();
    void next_state(Plane* plane);
    void sort_queue();
};

#endif