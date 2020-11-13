#include <iostream>
#include <vector>

#include "plane.h"
#include "person.h"
#include "queue.h"


using namespace std;


int main()
{
    Plane *plane = new Plane(20, {SEAT,SEAT,SEAT,HALL,SEAT,SEAT,SEAT});
    Queue* queue = new Queue(2);

    queue->fill_queue(plane);  
    queue->sort_queue();  

    do{
        queue->next_state(plane);

        plane->print_plane();
        sleep(1000);
    }while (!queue->all_seated());

    return 0;
}