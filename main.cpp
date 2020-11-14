#include <iostream>
#include <vector>

#include "plane.h"
#include "person.h"
#include "queue.h"


using namespace std;


int main()
{
    int rows, speed;
    vector<int> structure;
    read_configuration(rows, structure, speed);
    Plane *plane = new Plane(rows, structure);
    Queue* queue = new Queue(plane);
 
    queue->sort_queue();

    do{
        queue->next_state(plane);

        plane->print_plane();
        sleep(speed);
    }while (!queue->all_seated());

    return 0;
}