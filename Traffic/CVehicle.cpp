//
//  CVehicle.cpp
//  Traffic
//
//  Created by Emil Westholm on 2014-03-25.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#include "CVehicle.h"


CVehicle::CVehicle(int newId, enum Color color, float width, float height)
{
    Color = color;
    _id = newId;
    
    _speed = 100;
    Size = new CSize(width, height);
    
    switch(color){
        case Color::GREEN:
            _carType = "GreenCar";
            break;
        case Color::RED:
            _carType = "RedCar";
            break;
        case Color::BLUE:
            _carType = "BlueCar";
            break;
    }
}

string CVehicle::getCarType()
{
    return _carType;
}

float CVehicle::getSpeed()
{
    return _speed;
}

int CVehicle::getID()
{
    return _id;
}

/*string* CVehicle::getCarType()
{
    return _carType;
}

int CVehicle::getType()
{
    return _type;
}*/

bool CVehicle::EndOfTheRoad()
{
    if(this->CurrentLane != nullptr)
    {
        if(Position->getY() < this->CurrentLane->ENDOFTHELANE)
            return true;
    }
    
    return false;
}

bool CVehicle::IsToBeRemoved()
{
    return _toBeRemoved;
}

void CVehicle::MarkToBeRemoved()
{
    _toBeRemoved = true;
}

void CVehicle::Move(float x, float y)
{
    this->Position->setX(x);
    this->Position->setY(y);
}

bool CVehicle::IsNew()
{
    return _isNew;
}

void CVehicle::TurnOfIsNew()
{
    _isNew = false;
}