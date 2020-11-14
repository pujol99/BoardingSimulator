#include "queue.h"

Queue::Queue(Plane* plane){
    for (int i = 1; i < plane->rows; i++){
        for (int j = 0; j < plane->cols; j++){
            if(j == plane->hall)
                continue;
            Person *person = new Person(-1, -1, i, j);
            queue.push_back(person);
        }
    }

}

void Queue::print_queue(){
    for (int i = 0; i < queue.size(); i++){
        queue.at(i)->print_person();
    }
}

bool compare(Person* p1, Person* p2){
    return 0.2 > ((double) rand() / (RAND_MAX)) + 1;
}

void Queue::sort_queue(){
    std::sort(queue.begin(), queue.end(), compare);
}

bool Queue::all_seated(){
    for (int i = 0; i < queue.size(); i++)
    {
        if(queue.at(i)->state != SEATED)
            return false;
    }
    return true;
}

Person* Queue::get_person(int x, int y){
    for (int i = 0; i < queue.size(); i++)
    {
        if(queue.at(i)->x == x &&
            queue.at(i)->y == y){
            return queue.at(i);
        }
    }
    return NULL;
}

vector<Person*> Queue::get_persons(int x, int y){
    vector<Person*> persons;
    for (int i = 0; i < queue.size(); i++)
    {
        if(queue.at(i)->x == x &&
            queue.at(i)->y == y){
            persons.push_back(queue.at(i));
        }
    }
    return persons;
}

void Queue::next_state(Plane *plane){

    vector<int> persons_row;
    vector<int>::iterator int_i;

    vector<Person*> persons;
    vector<Person*>::iterator person_i;
    
    vector<Person*>::iterator queue_i = queue.begin();

    for(queue_i; queue_i != queue.end(); ++queue_i){

        Person* person = *queue_i;
        switch (person->state){
        case OUTSIDE:
            if(plane->is_clear(0, plane->hall)){
                person->enter_plane(plane->hall);
            }
            break;
        case WALKING:
            if(person->x == person->goalx){
                person->move_sideways();
            }else if (person->x == person->goalx - 1
                    && plane->is_clear(person->x+1, plane->hall)){
                persons_row = plane->leave_row(person->goalx, person->goaly);

                if(!persons_row.size()){
                    person->x++;
                    person->move_sideways();
                }else{
                    person->state = WAITING;

                    for(int_i = persons_row.begin(); int_i != persons_row.end(); ++int_i){
                        Person* person2 = get_person(person->goalx, *int_i);
                        if(person2->state == WALKING || person2->state == LEAVING)
                            break;
                    }                      
                    for(int_i = persons_row.begin(); int_i != persons_row.end(); ++int_i){
                        get_person(person->goalx, *int_i)->state = LEAVING;
                    }
                }
            }else if(plane->is_clear(person->x+1, plane->hall)){
                person->move_forwards();
            }
            break;
        case LEAVING:
            person->move_hall(plane->hall);
            break;
        case RETURNING:
            person->move_sideways();
            break;
        case WAITING:
            persons_row = plane->leave_row(person->goalx, person->goaly);
            if(!persons_row.size()){
                person->x++;
                person->move_sideways();
            }
            break;
        }
        plane->update_plane(queue);
    }

}
