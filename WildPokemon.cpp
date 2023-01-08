#include "WildPokemon.h"

WildPokemon::WildPokemon():GameObject('W'){
    name = "NoName";
    attack = 5;
    health = 2;
    variant = false;
    in_combat = false;
    current_trainer = 0;
    state = IN_ENVIRONMENT;
}

WildPokemon::WildPokemon(string name, double attack, double health, bool variant, int id, Point2D in_loc):GameObject(in_loc, id, 'W'){
    this->name = name;
    this->attack = attack;
    this->health = health;
    this->variant = variant;
    state = IN_ENVIRONMENT;
}

void WildPokemon::follow(Trainer* t){
    current_trainer = t;
    current_trainer->hasPokemon = true;     //signifies that the current trainer is being followed by a pokemon
    state = IN_TRAINER;
    //current_trainer->AddToHealth(health);
}

bool WildPokemon::get_variant(){
    return variant;
}

double WildPokemon::get_attack(){
    return attack;
}

double WildPokemon::get_health(){
    return health;
}

bool WildPokemon::get_in_combat(){
    return in_combat;
}

bool WildPokemon::Update(){
    if (state == IN_ENVIRONMENT)
        return true;
    else {
        if (health == 0) {
            state = DEAD;
            return false;
        }
        if (IN_TRAINER){
            //updates pokemon's location to match trainer's
            location = current_trainer->GetLocation();
            //decrements trainer's health more
            current_trainer -> PokemonHealthEffect(attack);
        }
        return true;
    }
    
}

void WildPokemon::ShowStatus(){
    cout << "WildPokemon " << name << " status: " << endl;
    GameObject::ShowStatus();

    if (IsAlive()){
        if (state == IN_TRAINER) {
            cout << "    In combat with trainer " << current_trainer->GetName() << endl;
        }
        if (state == IN_ENVIRONMENT)
            cout << "    in the environment." << endl;
        cout << "    Health: " << health << endl;
        cout << "    Attack: " << attack << endl;
        cout << "    Variant: " << variant << endl;
    }
    else {
        cout << "WildPokemon is dead." << endl;
    }  
}

bool WildPokemon::ShouldBeVisible(){
    if (IsAlive())
        return true;
    else
        return false;
}

bool WildPokemon::IsAlive(){
    if (health > 0)
        return true;
    else {
        state = DEAD;
        return false;
    }
}