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
    return 0.5 > ((double) rand() / (RAND_MAX)) + 1;
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

void Queue::next_state(Plane *plane)
{
    vector<Person *>::iterator it = queue.begin();
    vector<int> persons;
    vector<Person*> persons3;
    vector<int>::iterator it2;
    vector<Person*>::iterator it3;

    for(it; it != queue.end(); ++it)
    {
        Person* person = *it;
        switch (person->state){
        case OUTSIDE:
    
            if(plane->is_clear(0, plane->hall)){
                person->enter_plane(plane->hall);
                plane->plane[person->x][person->y] = PERSON;
            }
            break;
        case WALKING:
            if(person->x == person->goalx){
        
                person->move_sideways();
                plane->plane[person->x][person->y] = PERSON_SEAT;
            }else if (person->x == person->goalx - 1
                        && plane->is_clear(person->x+1, plane->hall)){
        
                persons = plane->row_clear(person->goalx, person->goaly);
                if(!persons.size()){
            
                    person->x++;
                    person->move_sideways();
                    plane->plane[person->x][person->y] = PERSON_SEAT;
                }else{
            
                    person->state = WAITING;
                    bool wait = false;
                    it2 = persons.begin();
                    for(it2; it2 != persons.end(); ++it2){
                        Person* person2 = get_person(person->goalx, *it2);
                        if(person2->state == WALKING || person2->state == LEAVING){
                            wait = true;
                        }    
                    }
                    if(wait)
                        break;
                       
                    it2 = persons.begin();
                    for(it2; it2 != persons.end(); ++it2){
                        get_person(person->goalx, *it2)->state = LEAVING;
                    }
                }
            }else if(plane->is_clear(person->x+1, plane->hall)){
        
                person->move_forwards();
                plane->plane[person->x][person->y] = PERSON;
            }
            break;
        case LEAVING:
    
            person->move_hall(plane->hall);
            if(person->state == RETURNING)
                break;
            plane->plane[person->x][person->y] = (person->y == HALL) ? PERSON : PERSON_SEAT;
            break;
        case RETURNING:
            if(person->y == plane->hall){
                persons = plane->row_clear(person->goalx, person->goaly);
                if(persons.size())
                    break;
                persons3 = get_persons(person->x, person->y);
                if(person->goaly > plane->hall){
                    int max_y = -1;
                    it3 = persons3.begin();
                    for(it3; it3 != persons3.end(); ++it3){
                        Person* p = *it3;
                        if(p->goaly > max_y)
                            max_y = p->goaly;
                    }
                    if(person->goaly != max_y)
                        break;
                }else{
                    int min_y = 999;
                    it3 = persons3.begin();
                    for(it3; it3 != persons3.end(); ++it3){
                        Person* p = *it3;
                        if(p->goaly < min_y)
                            min_y = p->goaly;
                    }
                    if(person->goaly != min_y)
                        break;
                }
            }
            person->move_sideways();
            plane->plane[person->x][person->y] = PERSON_SEAT;
            break;
        case WAITING:
            persons = plane->row_clear(person->goalx, person->goaly);
            if(!persons.size()){
                person->x++;
                person->move_sideways();
                plane->plane[person->x][person->y] = PERSON_SEAT;
            }
            break;
        }
        plane->update_plane(queue);
    }

}
