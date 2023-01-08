#include "Trainer.h"
#include "GameObject.h"
#include <math.h>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

Trainer::Trainer():GameObject('T'){
    speed = 5;
    state = STOPPED;
    name = "No Name";
    is_at_center = false;
    is_IN_GYM = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    current_center = 0;
    current_gym = 0;
    hasPokemon = false;         //variable to define whether a pokemon is following a trainer
    cout << "Trainer default constructed." << endl;
}

Trainer::Trainer(char in_code):GameObject(in_code){
    speed = 5;
    state = STOPPED;
    name = "No Name";
    is_at_center = false;
    is_IN_GYM = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    current_center = 0;
    current_gym = 0;
    hasPokemon = false;
    cout << "Trainer constructed." << endl;
}

Trainer::Trainer(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc):GameObject(in_loc, in_id, in_code){
    speed = in_speed;
    state = STOPPED;
    name = in_name;
    is_at_center = false;
    is_IN_GYM = false;
    health = 20;
    experience = 0;
    PokeDollars = 0;
    battles_to_buy = 0;
    potions_to_buy = 0;
    current_center = 0;
    current_gym = 0;
    hasPokemon = false;
    cout << "Trainer constructed." << endl;
}

Trainer::~Trainer(){
    cout << "Trainer destructed." << endl;
}

bool Trainer::UpdateLocation(){
    cout << display_code << id_num;
    double currentDeltaX = fabs(destination.x - location.x);
    double currentDeltaY = fabs(destination.y - location.y);
    if ((currentDeltaX <= fabs(delta.x)) && (currentDeltaY <= fabs(delta.y))){
        location = destination;
        cout << ": I'm there!" << endl;
        return true;
    } 
    else {
        location.x += delta.x;
        location.y += delta.y;
        health -= 1;
        PokeDollars += GetRandomAmountOfPokeDollars();
        cout << ": step..." << endl;
        return false;
    } 
}

void Trainer::SetupDestination(Point2D dest){
    destination = dest;
    Vector2D change = destination-location;
    double distBetween = GetDistanceBetween(destination, location);
    double inc = 0;
    if (distBetween != 0){
        inc = (double)speed/distBetween;
    }
    delta = change * inc;
}

void Trainer::StartMoving(Point2D dest){
    Trainer::SetupDestination(dest);
    cout << display_code << id_num;
    
    if (GetDistanceBetween(location,dest) == 0){
        cout << ": I'm already there. See?" << endl;
        UpdateLocation();
    }
    else if (state == FAINTED){
        cout << ": My pokemon have fainted. I may move but you cannot see me." << endl;
    }
    else {

        //accounts for leaving a center or gym
        if (state == AT_CENTER) {
            current_center->RemoveOneTrainer();
            is_at_center = false;
        }
        else if (state == IN_GYM) {
            current_gym->RemoveOneTrainer();
            is_IN_GYM = false;
        }

        //starts moving
        state = MOVING;
        cout << ": On my way." << endl;
    } 
}

void Trainer::StartMovingToGym(PokemonGym* gym){
    destination = (*gym).GetLocation();
    Trainer::SetupDestination(destination);
    UpdateLocation();
    cout << display_code << id_num;
    if (state == FAINTED)
        cout << ": My Pokemon have fainted so I can't move to gym..." << endl;
    else if (GetDistanceBetween( destination, location ) == 0) {
        UpdateLocation();
        cout << ": I am already at the PokemonGym!" << endl;
    }
    else {

        //accounts for leaving a center or gym
        if (state == AT_CENTER){
            current_center->RemoveOneTrainer();
            is_at_center = false;
        }
        else if (state == IN_GYM) {
            current_gym->RemoveOneTrainer();
            is_IN_GYM = false;
        }

        //starts moving to gym
        state = MOVING_TO_GYM;
        current_gym = gym;
        cout << ": On my way to gym " << (*gym).GetId() << endl;
    }
}

void Trainer::StartMovingToCenter(PokemonCenter* center){
    destination = (*center).GetLocation();
    SetupDestination(destination);
    UpdateLocation();
    cout << display_code << id_num;

    if (state == FAINTED)
        cout << ": My Pokemon have fainted so I should have gone to the center." << endl;
    else if (GetDistanceBetween(destination, location) == 0) {
        state = AT_CENTER;
        cout << ": I am already at the Center!" << endl;
        UpdateLocation();
    }
    else {

        //accounts for leaving a center or gym
        if (state == AT_CENTER) {
            current_center->RemoveOneTrainer();
            is_at_center = false;
        }
        else if (state == IN_GYM) {
            current_gym->RemoveOneTrainer();
            is_IN_GYM = false;
        }

        //starts moving to center
        state = MOVING_TO_CENTER;
        current_center = center;
        cout << ": On my way to center " << (*center).GetId() << endl;
    }
}

void Trainer::StartBattling(unsigned int num_battles){
    if (current_gym != NULL) {
        cout << display_code << id_num;
        if (state == FAINTED)
            cout << ": My Pokemon have fainted so no more battles for me..." << endl;
        else if (!is_IN_GYM)
            cout << ": I can only battle in a PokemonGym!" << endl;
        else if (PokeDollars < current_gym->GetPokeDollarCost(num_battles))
            cout << ": Not enough money for battles." << endl;
        else if ((*current_gym).GetTrainerCount() <= 0)
            cout << ": Cannot battle! This PokemonGym has no more trainers to battle!" << endl;
        else {
            cout << display_code << ": Started to battle at the PokemonGym " << (*current_gym).GetId() << " with " << num_battles << " battles." << endl;
            state = BATTLING_IN_GYM;
            battles_to_buy = num_battles;
            current_gym->SubBattles(num_battles);   //alters number of battles in gym
        }
    }
}

void Trainer::StartRecoveringHealth(unsigned int num_potions){
    if (current_center != NULL) {
        state = RECOVERING_HEALTH;
        cout << display_code << id_num;
        
        if (!current_center->CanAffordPotion(potions_to_buy, PokeDollars))
            cout << ": Not enough money to recover health." << endl;
        else if (!current_center->HasPotions())
            cout << ": Cannot recover! No potions remaining in this PokemonCenter." << endl;
        else if (!is_at_center)
            cout << ": I can only recover health at a Pokemon Center!" << endl;
        else {
            potions_to_buy = current_center->DistributePotion(num_potions);
            state = RECOVERING_HEALTH;
            health += 5;
            cout << ": Started recovering " << potions_to_buy << " potions at PokemonCenter " << id_num << endl;
        }
    }
}

void Trainer::Stop(){
    state = STOPPED;
    cout << display_code << id_num << ": Stopping..." << endl;
}

bool Trainer::HasFainted(){
    if (health == 0) {
        state = FAINTED;
        return true;
    }
    else
        return false;
}

bool Trainer::ShouldBeVisible(){
    if (state != FAINTED)
        return true;
    else 
        return false;
}

void Trainer::ShowStatus(){
    cout << name << " status:" << endl;
    GameObject::ShowStatus();

    if (state == STOPPED)
        cout << " stopped." << endl;
    else if (state == MOVING)
        cout << " moving at a speed of " << speed << " to destination " << destination << " at each step of " << delta << "." << endl;
    if (current_center != NULL || current_gym != NULL) {
        if (state == MOVING_TO_GYM)
            cout << " heading to PokemonGym " << (*current_gym).GetId() << " at a speed of " << speed << " at each step of " << delta << "." << endl;
        else if (state == MOVING_TO_CENTER)
            cout << " heading to PokemonCenter " << current_center->GetId() << " at a speed of " << speed << " at each step of " << delta << "." << endl;
        else if (state == IN_GYM)
            cout << " inside PokemonGym " << (*current_gym).GetId() << endl;
        else if (state == AT_CENTER)
            cout << " inside Pokemon Center " << (*current_center).GetId() << endl;
        else if (state == BATTLING_IN_GYM)
            cout << " battling in PokemonGym " << (*current_gym).GetId() << endl;
        else if (state == RECOVERING_HEALTH)
            cout << " recovering health in Pokemon Center " << (*current_center).GetId() << endl;
    }
    if (hasPokemon){
        cout << name << " is being followed by pokemon." << endl;
    }

    cout << "Health: " << health << endl;
    cout << "PokeDollars: " << PokeDollars << endl;
    cout << "Experience: " << experience << endl;
}


bool Trainer::Update(){
    bool stateChange = false;

    if (state == MOVING){
        if (UpdateLocation()) {
            state = STOPPED;
            stateChange = true;
        }
    }

    else if (state == MOVING_TO_GYM){
        if (UpdateLocation()) {         //reached gym
            state = IN_GYM;
            is_IN_GYM = true;
            (*current_gym).AddOneTrainer();
            stateChange = true;
        }
    }
        
    else if (state == MOVING_TO_CENTER){
        if (UpdateLocation()) {         //reached center
            state = AT_CENTER;  
            is_at_center = true;
            (*current_center).AddOneTrainer(); 
            stateChange = true;
        }
    }

    else if (state == BATTLING_IN_GYM){
        //UpdateLocation();
        health -= (*current_gym).GetHealthCost((*current_gym).GetNumBattlesRemaining());
        PokeDollars -= (*current_gym).GetPokeDollarCost((*current_gym).GetNumBattlesRemaining());
        experience += (*current_gym).TrainPokemon((*current_gym).GetNumBattlesRemaining());
        cout << "* " << name << " completed " << (*current_gym).GetNumBattlesRemaining() << " battle(s)! *" << endl;
        cout << "* " << name << " gained " << experience << " experience! *" << endl;
        state = IN_GYM;
        stateChange = true;
    }

    else if (state == RECOVERING_HEALTH){
        //UpdateLocation();
        StartRecoveringHealth(potions_to_buy);
        PokeDollars -= current_center->GetPokeDollarCost(potions_to_buy);
        cout << "** " << name << " recovered  " << health << " health! **" << endl;
        cout << "** " << name << " bought " << potions_to_buy << " potion(s)! **" << endl;
        state = AT_CENTER;
        stateChange = true;
    }    

    if (health == 0){
        state = FAINTED;
        cout << name << " is out of health and can't move." << endl;
    }

    return stateChange;

}

//Getter function that returns the given trainer's name
string Trainer::GetName(){
    return name;
}

//function that decrements the trainer's health if a Pokemon is following it
void Trainer::PokemonHealthEffect(double decrement){
    if (health > 0)
        health = health - decrement;
}


double GetRandomAmountOfPokeDollars(){  
    srand(time(NULL));                      //sets random time seed
    double f = (double)rand() / RAND_MAX;
    return f * (2);
}