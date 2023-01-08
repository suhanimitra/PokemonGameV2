#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>
#include "GameObject.h"
#include "Point2D.h" 

class Building: public GameObject {
    private:
        static unsigned int trainer_count;

    public:
        Building();
        Building(char in_code, int in_id, Point2D in_loc);
        void AddOneTrainer();
        void RemoveOneTrainer();
        void ShowStatus();
        bool ShouldBeVisible();
        unsigned int GetTrainerCount();
};

#endif