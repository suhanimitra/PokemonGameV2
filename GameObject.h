#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Point2D.h"
#include <iostream>

class GameObject{

    protected:
        Point2D location;
        int id_num;
        char display_code;
        char state;
    
    //public member functions
    public:
        GameObject(char in_code);
        GameObject(Point2D in_loc, int in_id, char in_code);
        virtual ~GameObject();
        Point2D GetLocation();
        int GetId();
        char GetState();
        char GetDisplayCode();
        virtual void ShowStatus();
        virtual bool Update() = 0;
        virtual bool ShouldBeVisible() = 0;
        void DrawSelf(char * ptr);
};

#endif