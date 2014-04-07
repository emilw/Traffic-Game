//
//  CVehicle.h
//  Traffic
//
//  Created by Emil Westholm on 2014-03-25.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#ifndef __Traffic__CVehicle__
#define __Traffic__CVehicle__

#include <iostream>
#include <string>
#include "CPosition.h"
#include "CLane.h"
#include "CSize.h"
#include "SharedEnum.h"
#include "CFrame.h"

using namespace std;

class CVehicle: public CFrame
{
    
private:
    int _id;
    string _carType;
    //int _type;
    float _speed;
    bool _toBeRemoved = false;
    bool _isNew = true;
public:
    CVehicle(int newId, Color color, float width, float height);
    Color Color;
    
    bool IsNew();
    void TurnOfIsNew();
    
    //Getters
    int getID();
    string getCarType();
    //int getType();
    float getSpeed();
    
    //External objects
    //CPosition* Position;
    //CSize* Size;
    CLane* CurrentLane;
    
    //Methods
    bool EndOfTheRoad();
    //bool IsCollision(CVehicle* otherVehicle);
    void Move(float x, float y);
    
    //Cordinates methods
    /*float GetX1();
    float GetX2();
    float GetY1();
    float GetY2();*/
    
    bool IsToBeRemoved();
    void MarkToBeRemoved();
};

#endif /* defined(__Traffic__CVehicle__) */
