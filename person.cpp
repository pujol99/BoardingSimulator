#include "person.h"

Person::Person(int x, int y, int goalx, int goaly){
    this->x = x;
    this->y = y;
    this->goalx = goalx;
    this->goaly = goaly;
    this->state = OUTSIDE;
}

void Person::print_person(){
    cout << "from (" << this->x << ", " << this->y << ")";
    cout << " to (" << this->goalx << ", " << this->goaly << "), ";
    switch (state)
    {
    case SEATED:
        cout << "seated\n";
        break;
    case OUTSIDE:
        cout << "outside\n";
        break;
    case WALKING:
        cout << "walking\n";
        break;
    case RETURNING:
        cout << "returning\n";
        break;
    case LEAVING:
        cout << "leaving\n";
        break;
    case WAITING:
        cout << "waiting\n";
        break;
    }
}

void Person::move_forwards(){
    x++;
    state = WALKING;
}

void Person::move_sideways(){
    y = (goaly > y) ? y + 1 : y - 1;
    state = WALKING;
    in_goal();
}

void Person::move_hall(int hall){
    if(y == hall)
        state = RETURNING;
    else
        y = (goaly > hall) ? y - 1 : y + 1;
    
}

void Person::enter_plane(int hall){
    x = 0;
    y = hall;
    state = WALKING;
}

void Person::in_goal(){
    if(x == goalx && y == goaly){
        state = SEATED;
    }   
}