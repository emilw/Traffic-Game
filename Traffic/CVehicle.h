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

using namespace std;

class CVehicle{
    
private:
    int _id;
    string* _carType;
    int _type;
    float _speed;
    
public:
    CVehicle(int newId, string* newCarType, int type);
    int getID();
    string* getCarType();
    int getType();
    CPosition* Position;
    float getSpeed();
    CLane* GoalLane;
};

#endif /* defined(__Traffic__CVehicle__) */
