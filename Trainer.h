#ifndef TRAINER_H
#define TRAINER_H

#include <iostream>
#include <string>
#include "GameObject.h"
#include "Point2D.h"
#include "Vector2D.h"
#include "PokemonCenter.h"
#include "Building.h"
#include "PokemonGym.h"
#include <time.h>
#include <stdlib.h>

using namespace std;

enum TrainerStates {
    STOPPED = 0,
    MOVING = 1,
    FAINTED = 2, 
    AT_CENTER = 3,
    IN_GYM = 4,
    MOVING_TO_CENTER = 5,
    MOVING_TO_GYM = 6,
    BATTLING_IN_GYM = 7,
    RECOVERING_HEALTH = 8
};


class Trainer: public GameObject{

    private:
        double speed;
        bool is_at_center;
        bool is_IN_GYM;
        unsigned int health;
        unsigned int experience;
        double PokeDollars;
        unsigned int battles_to_buy;
        unsigned int potions_to_buy;
        string name;
        PokemonCenter* current_center;
        PokemonGym* current_gym;
        Point2D destination;
        Vector2D delta;

    protected:
        bool UpdateLocation();
        void SetupDestination(Point2D dest);
    
    public:
        bool hasPokemon;

    public:
        Trainer();
        Trainer(char in_code);
        Trainer(string in_name, int in_id, char in_code, unsigned int in_speed, Point2D in_loc);
        virtual ~Trainer();
        void StartMoving(Point2D dest);
        void StartMovingToGym(PokemonGym* gym);
        void StartMovingToCenter(PokemonCenter* center);
        void StartBattling(unsigned int num_battles);
        void StartRecoveringHealth(unsigned int num_potions);
        void Stop();
        bool HasFainted();
        bool ShouldBeVisible();
        void ShowStatus();
        bool Update();
        string GetName();
        void PokemonHealthEffect(double decrement);
    
};

double GetRandomAmountOfPokeDollars();

#endif