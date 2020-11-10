#include <iostream>
#include <vector>
#include "plane.h"
#include "person.h"

using namespace std;

vector<Person*> init_queue(int size){
    vector<Person*> queue;
    for(int i = 0; i < 30; i++){
        Person* person = new Person(-1, -1, -1, -1);
        queue.push_back(person);
    }
    return queue
}

int main() {
    int col_structure[7] = {1,1,1,0,1,1,1};
    Plane* plane = new Plane(40, col_structure, 7);

    vector<Person*> queue = init_queue(30);

    return 0;
}