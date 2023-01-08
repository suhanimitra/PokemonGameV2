#include "Building.h"

using namespace std;

unsigned int Building::trainer_count = 0; 

Building::Building() :GameObject('B') {
    cout << "Building default constructed." << endl;
}

Building::Building(char in_code, int in_id, Point2D in_loc) :GameObject(in_loc, in_id, in_code) {
    display_code = in_code;
    id_num = in_id;
    location = in_loc;
    cout << "Building constructed." << endl;
}

void Building::AddOneTrainer(){
    trainer_count ++;
}
 
void Building::RemoveOneTrainer(){
    trainer_count--;
}

void Building::ShowStatus(){
    cout << display_code << id_num << " located at " << location << endl;
    if (trainer_count == 1){
        cout << trainer_count << " trainer is in this building" << endl;
    }
    else {
        cout << trainer_count << " trainers are in this building" << endl;
    }
}

bool Building::ShouldBeVisible(){
    return true;
}

//Function that returns how many trainers are currently in the building
unsigned int Building::GetTrainerCount(){
    return Building::trainer_count;
}