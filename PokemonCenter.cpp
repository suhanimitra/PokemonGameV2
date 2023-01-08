#include "PokemonCenter.h"

PokemonCenter::PokemonCenter():Building(){
    display_code = 'C';
    potion_capacity = 100;
    num_potions_remaining = potion_capacity;
    pokedollar_cost_per_potion = 5;
    state = POTIONS_AVAILABLE;
    cout << "PokemonCenter default constructed." << endl;
}

PokemonCenter::PokemonCenter (int in_id, double potion_cost, unsigned int potion_cap, Point2D in_loc):Building('C', in_id, in_loc){
    state = POTIONS_AVAILABLE;
    potion_capacity = potion_cap;
    num_potions_remaining = potion_capacity;
    pokedollar_cost_per_potion = potion_cost;
    cout << "PokemonCenter constructed." << endl;
}

PokemonCenter::~PokemonCenter(){
    cout << "PokemonCenter destructed." << endl;
}

bool PokemonCenter::HasPotions(){
    bool hasPotions = false;
    if (num_potions_remaining > 0){
        hasPotions = true;
    }
    return hasPotions;
}

unsigned int PokemonCenter::GetNumPotionRemaining(){
    return num_potions_remaining; 
}

bool PokemonCenter::CanAffordPotion(unsigned int potion, double budget){
    bool canBuy = false;
    if (budget >= GetPokeDollarCost(potion)){
        canBuy = true;
    }
    return canBuy;
}

double PokemonCenter::GetPokeDollarCost(unsigned int potion){
    return pokedollar_cost_per_potion * potion;
}

unsigned int PokemonCenter::DistributePotion(unsigned int potion_needed){
    int returnPotions;
    if (num_potions_remaining >= potion_needed){
        num_potions_remaining -= potion_needed;
        returnPotions = potion_needed;
    }
    else {
        returnPotions = num_potions_remaining;
        num_potions_remaining = 0;
    }
    return returnPotions;

}


bool PokemonCenter::Update(){
    if (num_potions_remaining == 0 && outOfPotionsOnce){
        state = NO_POTIONS_AVAILABLE;
        display_code = 'c';
        cout << "PokemonCenter " << id_num << " has ran out of potions." << endl;
        outOfPotionsOnce = false;
        return true;
    }
    else   
        return false;
}

void PokemonCenter::ShowStatus(){
    cout << "PokemonCenter Status: " << endl;;
    Building::ShowStatus();
    cout << "PokeDollars per potion: " << pokedollar_cost_per_potion << endl;
    cout << "has " << num_potions_remaining << " potion(s) remaining." << endl;
} 