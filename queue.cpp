#include "queue.h"

Queue::Queue(int size){
    for (int i = 0; i < size; i++){
        Person *person = new Person(-1, -1, -1, -1);
        queue.push_back(person);
    }
}

void Queue::print_queue(){
    for (int i = 0; i < queue.size(); i++){
        queue.at(i)->print_person();
    }
}

void Queue::fill_queue(Plane* plane)
{
    int j = 0,k = 0, row, col;
    for (int i = 0; i < queue.size(); i++){
        // row = plane->rows - 1 - i;
        // queue.at(i)->goalx = row;
        // col = j%plane->cols;
        // if(plane->plane[row][col] == HALL)
        //     j++;
        // queue.at(i)->goaly = j % plane->cols;
        // j += 5;
        row = 4;
        queue.at(i)->goalx = row;
        col = j%plane->cols;
        if(plane->plane[row][col] == HALL)
            j++;
        queue.at(i)->goaly = j % plane->cols;
        j++;
    }
}

bool compare(Person* p1, Person* p2){
    return (p1->goaly >= p2->goaly);
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

void Queue::next_state(Plane *plane)
{
    vector<Person *>::iterator it = queue.begin();
    vector<int> persons;
    vector<int>::iterator it2;

    for(it; it != queue.end(); ++it)
    {
        Person* person = *it;
        int prevx = person->x, prevy = person->y;
        person->print_person();
        switch (person->state){
        case OUTSIDE:
            cout << "Outside\n";
            if(plane->is_clear(0, plane->hall)){
                person->enter_plane(plane->hall);
                plane->plane[person->x][person->y] = PERSON;
            }
            break;
        case WALKING:
            if(person->x == person->goalx){
                cout << "Walking in col\n";
                person->move_sideways();
                plane->plane[person->x][person->y] = PERSON_SEAT;
                plane->plane[prevx][prevy] = plane->original[prevx][prevy];
            }else if (person->x == person->goalx - 1
                        && plane->is_clear(person->x+1, plane->hall)){
                cout << "Looking for people in row, ";
                persons = plane->row_clear(person->goalx, person->goaly);
                if(!persons.size()){
                    cout << "no people\n";
                    person->x++;
                    person->move_sideways();
                    plane->plane[person->x][person->y] = PERSON_SEAT;
                    plane->plane[prevx][prevy] = plane->original[prevx][prevy];
                }else{
                    cout << "yes people\n";
                    bool wait = false;
                    it2 = persons.begin();
                    for(it2; it2 != persons.end(); ++it2){
                        get_person(person->goalx, *it2)->print_person();
                        if(get_person(person->goalx, *it2)->state == WALKING ||
                            get_person(person->goalx, *it2)->state == LEAVING){
                            wait = true;
                            person->state = WAITING;
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
                cout << "Moving forward\n";
                person->move_forwards();
                plane->plane[person->x][person->y] = PERSON;
                plane->plane[prevx][prevy] = plane->original[prevx][prevy];
            }
            break;
        case LEAVING:
            cout << "Leaving\n";
            person->move_hall(plane->hall);
            if(person->state == RETURNING)
                break;
            plane->plane[person->x][person->y] = (person->y == HALL) ? PERSON : PERSON_SEAT;
            plane->plane[prevx][prevy] = plane->original[prevx][prevy];
            break;
        case RETURNING:
            cout << "Returning, ";
            persons = plane->row_clear(person->goalx, person->goaly);
            if(persons.size()){
                cout << "Persons inside\n";
                break;
            }cout << "No Persons inside\n";
                
            person->move_sideways();
            plane->plane[person->x][person->y] = PERSON_SEAT;
            if(prevy == plane->hall)
                plane->plane[prevx][prevy] = get_person(prevx, prevy) ? PERSON : HALL;
            else
                plane->plane[prevx][prevy] = plane->original[prevx][prevy];
            break;
        case WAITING:
            cout << "Waitin, ";
            persons = plane->row_clear(person->goalx, person->goaly);
            if(!persons.size()){
                cout << "no people\n";
                person->x++;
                person->move_sideways();
                plane->plane[person->x][person->y] = PERSON_SEAT;
                plane->plane[prevx][prevy] = plane->original[prevx][prevy];}
            cout << "yes people\n";
            break;
        }
    }

}
