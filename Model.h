#ifndef MODEL_H
#define MODEL_H

#include "Model.h"
#include <iostream>
#include "GameObject.h"
#include "PokemonCenter.h"
#include "PokemonGym.h"
#include "View.h"
#include "Trainer.h"
#include "WildPokemon.h"
#include "Invalid_Input.h"
#include <list>
#include <iterator>
 
using namespace std;

class Model {
    private:
        int time;
        list<GameObject*> object_ptrs;
        list<GameObject*> active_ptrs;
        list<Trainer*> trainer_ptrs;
        list<PokemonCenter*> center_ptrs;
        list<PokemonGym*> gym_ptrs;
        list<WildPokemon*> wildpokemon_ptrs;

        //iterators
        
        list<GameObject*>::iterator objIt;
        list<GameObject*>::iterator activeIt;
        list<Trainer*>::iterator trainerIt;
        list<PokemonCenter*>::iterator centerIt;
        list<PokemonGym*>::iterator gymIt;
        list<WildPokemon*>::iterator wildPokeIt;

    public:
        Model();
        ~Model();
        Trainer * GetTrainerPtr(int id);
        PokemonCenter * GetPokemonCenterPtr(int id);
        PokemonGym * GetPokemonGymPtr(int id);
        WildPokemon * GetWildPokemonPtr(int id);
        bool Update();
        void Display(View& view);
        void ShowStatus();
        void atTrainerLoc();
        void NewCommand(char type, int id, Point2D loc);
};

#endif