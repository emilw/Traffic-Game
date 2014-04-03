//
//  CVehicle.cpp
//  Traffic
//
//  Created by Emil Westholm on 2014-03-25.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#include "CVehicle.h"


CVehicle::CVehicle(int newId, enum Color color)//string* newCarType, int type)
{
    Color = color;
    _id = newId;
    //_carType = newCarType;
    //_type = type;
    _speed = 100;
    Position = new CPosition(0,0);
    Size = new CSize(65, 58);
}

bool CVehicle::IsCollision(CVehicle *otherVehicle)
{
    //Get the cordinates for the otherVehicle
    if(otherVehicle->GetX1() < this->GetX2() &&
       otherVehicle->GetX2() > this->GetX1() &&
       otherVehicle->GetY1() < this->GetY2() &&
       otherVehicle->GetY2() > this->GetY1()){
        return true;
    }
    
    return false;
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
    if(Position->getY() < this->CurrentLane->ENDOFTHELANE)
        return true;
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

float CVehicle::GetX1()
{
    return this->Position->getX() - (this->Size->GetWidth()/2);
}

float CVehicle::GetX2()
{
    return this->Position->getX() + (this->Size->GetWidth()/2);
}

float CVehicle::GetY1()
{
    return this->Position->getY() - (this->Size->GetHeight()/2);
}

float CVehicle::GetY2()
{
    return this->Position->getY() + (this->Size->GetHeight()/2);
}