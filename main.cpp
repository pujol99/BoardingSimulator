#include <iostream>
#include <vector>

#include "plane.h"
#include "person.h"
#include "queue.h"


using namespace std;


int main()
{
    Plane *plane = new Plane(10, {SEAT,SEAT,SEAT,HALL,SEAT,SEAT,SEAT});
    Queue* queue = new Queue(plane);
 
    queue->sort_queue();

    do{
        queue->next_state(plane);

        plane->print_plane();
        sleep(100);
    }while (!queue->all_seated());

    return 0;
}