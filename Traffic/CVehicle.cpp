//
//  CVehicle.cpp
//  Traffic
//
//  Created by Emil Westholm on 2014-03-25.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#include "CVehicle.h"


CVehicle::CVehicle(int newId, string* newCarType, int type)
{
    _id = newId;
    _carType = newCarType;
    _type = type;
    _speed = 100;
    Position = new CPosition(0,0);
}

float CVehicle::getSpeed()
{
    return _speed;
}

int CVehicle::getID()
{
    return _id;
}

string* CVehicle::getCarType()
{
    return _carType;
}

int CVehicle::getType()
{
    return _type;
}