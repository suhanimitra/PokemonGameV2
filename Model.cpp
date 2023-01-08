#include "Model.h"
#include "Trainer.h"
#include <iostream>
#include "GameObject.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "View.h"
#include "WildPokemon.h"
#include "Invalid_Input.h"
#include <list>
 
using namespace std;

Model::Model(){

    time = 0;

    //Initializes various locations for each building object that is created
    Point2D t1Loc(5,1); 
    Point2D t2Loc(10,1);
    Point2D c1Loc(1,20);
    Point2D c2Loc(10,20);
    Point2D g1Loc(0,0);
    Point2D g2Loc(5,5);
    Point2D w1Loc(10,12);
    Point2D w2Loc(15,5);

    PokemonCenter* C1 = new PokemonCenter(1, 1, 100, c1Loc);
    PokemonCenter* C2 = new PokemonCenter(2, 2, 200, c2Loc);

    center_ptrs.push_back(C1);
    center_ptrs.push_back(C2);

    PokemonGym* G1 = new PokemonGym(10, 1, 2, 3, 1, g1Loc);
    PokemonGym* G2 = new PokemonGym(20, 5, 7.5, 4, 2, g2Loc);
    
    gym_ptrs.push_back(G1);
    gym_ptrs.push_back(G2);

    Trainer* T1 = new Trainer("Ash", 1, 'T', 1, t1Loc);
    Trainer* T2 = new Trainer("Misty", 2, 'T', 2, t2Loc);

    trainer_ptrs.push_back(T1);
    trainer_ptrs.push_back(T2);

    WildPokemon* W1 = new WildPokemon("Meowth", 2, 8, false, 1, w1Loc);
    WildPokemon* W2 = new WildPokemon("Snorlax", 3, 10, false, 2, w2Loc);

    wildpokemon_ptrs.push_back(W1);
    wildpokemon_ptrs.push_back(W2);

    object_ptrs.push_back(C1);
    object_ptrs.push_back(C2);
    object_ptrs.push_back(G1);
    object_ptrs.push_back(G2);
    object_ptrs.push_back(T1);
    object_ptrs.push_back(T2);
    object_ptrs.push_back(W1);
    object_ptrs.push_back(W2);


    //since all objects are active upon construction
    active_ptrs.push_back(C1);
    active_ptrs.push_back(C2);
    active_ptrs.push_back(G1);
    active_ptrs.push_back(G2);
    active_ptrs.push_back(T1);
    active_ptrs.push_back(T2);
    active_ptrs.push_back(W1);
    active_ptrs.push_back(W2);

    //initialize iterators for each list
    /*
    objIt = object_ptrs.begin();
    activeIt = active_ptrs.begin();
    trainerIt = trainer_ptrs.begin();
    centerIt = center_ptrs.begin();
    gymIt = gym_ptrs.begin();
    wildPokeIt = wildpokemon_ptrs.begin();
    */

    cout << "Model default constructed." << endl;

}


Model::~Model(){
    for (objIt = object_ptrs.begin(); objIt != object_ptrs.end(); ++objIt){
        delete *objIt;
    }
    cout << "Model destructed." << endl;
}

Trainer* Model::GetTrainerPtr(int id){
    for (trainerIt = trainer_ptrs.begin(); trainerIt != trainer_ptrs.end(); ++trainerIt){
        if ((*trainerIt)->GetId() == id)
            return *trainerIt;
    }
}

PokemonCenter* Model::GetPokemonCenterPtr(int id){
    for (centerIt = center_ptrs.begin(); centerIt != center_ptrs.end(); ++centerIt){
        if ((*centerIt)->GetId() == id)
            return *centerIt;
    }
}

PokemonGym* Model::GetPokemonGymPtr(int id){
    for (gymIt = gym_ptrs.begin(); gymIt != gym_ptrs.end(); ++gymIt){
        if ((*gymIt)->GetId() == id)
            return *gymIt;
    }
}

WildPokemon* Model::GetWildPokemonPtr(int id){
    for (wildPokeIt = wildpokemon_ptrs.begin(); wildPokeIt != wildpokemon_ptrs.end(); ++wildPokeIt){
        if ((*wildPokeIt)->GetId() == id)
            return *wildPokeIt;
    }
}


bool Model::Update(){
    time++;
    int notFaintCount = 0;
    int hasBattles = 0;
    bool objectResult = false;
    bool oneObjTrue = false;
    int i = 0;

    atTrainerLoc();     //check if a trainer and pokemon are at the same location

    for (activeIt = active_ptrs.begin(); activeIt != active_ptrs.end(); ++activeIt){
        
        objectResult = (*activeIt)->Update();
        if (objectResult && !oneObjTrue){
            oneObjTrue = true;      //gets return value if one object's update function returns true
        }
        
        if (trainer_ptrs.size() > 0 && i < trainer_ptrs.size()) {
            for (trainerIt = trainer_ptrs.begin(); trainerIt != trainer_ptrs.end(); ++trainerIt) {
                if (!(*trainerIt)->HasFainted()){
                    notFaintCount++;               //increments if a trainer hasn't fainted, so if all are fainted, it = 0
                }
                else {
                    //remove trainer if it faints
                    active_ptrs.remove(*trainerIt);
                    cout << "Dead object removed." << endl;
                }
            }
        } 

        if (gym_ptrs.size() > 0 && i < gym_ptrs.size()) {
            for (gymIt = gym_ptrs.begin(); gymIt != gym_ptrs.end(); ++gymIt) {
                if ((*gymIt)->GetNumBattlesRemaining() != 0){
                        hasBattles++;            //increments if a gym still has battles, so if there are non, it = 0
                }
                else {
                    //remove gym if it runs out of battles
                    active_ptrs.remove(*gymIt);
                    cout << "Dead object removed." << endl;
                }
            }
        }

        if (wildpokemon_ptrs.size() > 0 && i < wildpokemon_ptrs.size()) {
            for (wildPokeIt = wildpokemon_ptrs.begin(); wildPokeIt != wildpokemon_ptrs.end(); ++wildPokeIt) {
                if ((*wildPokeIt)->get_health() == 0) {
                    //remove pokemon if it dies
                    active_ptrs.remove(*wildPokeIt);
                    cout << "Dead object removed." << endl;
                }
            }
        }

        i++;
    }

    if (hasBattles == 0 ){
        cout << "GAME OVER: You win! All battles done!" << endl;
        exit(EXIT_SUCCESS);
    }

    if (notFaintCount == 0){
        cout << "GAME OVER: You lose! All of your Trainer's pokemon have fainted!" << endl;
        exit(EXIT_SUCCESS);
    }

    return oneObjTrue;
}

void Model::Display(View& view){
    cout << "Time: " << time << endl;
    view.Clear();
    for (activeIt = active_ptrs.begin(); activeIt != active_ptrs.end(); ++activeIt) {
        view.Plot(*activeIt);
    }
    view.Draw();
}


void Model::ShowStatus(){
    cout << "Time: " << time << endl;
    for (objIt = object_ptrs.begin(); objIt != object_ptrs.end(); ++objIt){
        (*objIt)->ShowStatus();
    }
}

//function to see if a trainer and pokemon are at the same location
void Model::atTrainerLoc(){
    for (wildPokeIt = wildpokemon_ptrs.begin(); wildPokeIt != wildpokemon_ptrs.end(); ++wildPokeIt){
        for (trainerIt = trainer_ptrs.begin(); trainerIt != trainer_ptrs.end(); ++trainerIt){
            Point2D pokeLoc = (*wildPokeIt)->GetLocation();
            Point2D trainerLoc = (*trainerIt)->GetLocation();
            //if they are in the same location
            if (GetDistanceBetween(pokeLoc, trainerLoc) == 0) {
                (*wildPokeIt)->follow(*trainerIt);
            }
        }
    }
}


//function that aids creating objects at runtime
void Model::NewCommand(char type, int id, Point2D loc){
    bool objectAlreadyExists = false;
    if (type == 'c'){
        //checks if the object already exists
        for (centerIt = center_ptrs.begin(); centerIt != center_ptrs.end(); ++centerIt){
            if ((*centerIt)->GetId() == id){
                objectAlreadyExists = true;
            }
        }
        if (!objectAlreadyExists && id <=9)  {
            PokemonCenter* const addCenter = new PokemonCenter(id, 1, 100, loc);
            center_ptrs.push_back(addCenter);
            active_ptrs.push_back(addCenter);
            object_ptrs.push_back(addCenter);
        }
        else {
            throw Invalid_Input("PokemonCenter with this ID already exists!");
        } 
    }
    else if (type == 'g'){
        //checks if the object already exists
        for (gymIt = gym_ptrs.begin(); gymIt != gym_ptrs.end(); ++gymIt){
            if ((*gymIt)->GetId() == id){
                objectAlreadyExists = true;
            }
        }
        if (!objectAlreadyExists && id <=9 ) {
            PokemonGym* const addGym = new PokemonGym(10, 1, 2, 3, id, loc);
            gym_ptrs.push_back(addGym);
            active_ptrs.push_back(addGym);
            object_ptrs.push_back(addGym);
        }
        else {
            throw Invalid_Input("PokemonGym with this ID already exists!");
        }   

    }

    else if (type == 't'){
        //checks if the object already exists
        for (trainerIt = trainer_ptrs.begin(); trainerIt != trainer_ptrs.end(); ++trainerIt){
            if ((*trainerIt)->GetId() == id){
                objectAlreadyExists = true;
            }
        }
        if (!objectAlreadyExists && id <=9) {
            Trainer* const addTrainer = new Trainer("NoName", id, 'T', 1, loc);
            trainer_ptrs.push_back(addTrainer);
            active_ptrs.push_back(addTrainer);
            object_ptrs.push_back(addTrainer);
        }
        else {
            throw Invalid_Input("Trainer with this ID already exists!");
        }

    }

    else if (type == 'w'){
        //checks if the object already exists
        for (wildPokeIt = wildpokemon_ptrs.begin(); wildPokeIt != wildpokemon_ptrs.end(); ++wildPokeIt){
            if ((*wildPokeIt)->GetId() == id){
                objectAlreadyExists = true;
            }
        }
        if (!objectAlreadyExists && id <=9) {
            WildPokemon* const addPokemon = new WildPokemon("Pikachu", 2, 8, false, 1, loc);
            wildpokemon_ptrs.push_back(addPokemon);
            active_ptrs.push_back(addPokemon);
            object_ptrs.push_back(addPokemon);
        }
        else {
            throw Invalid_Input("WildPokemon with this ID already exists!");
        }

    }

    else {
        throw Invalid_Input("Invalid code");
    }
}