//
//  CEngine.cpp
//  Traffic
//
//  Created by Emil Westholm on 2014-03-09.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#include "CEngine.h"

CLane* CEngine::GetNewLane()
{
    CLane* newLane = new CLane(this->getNextLaneId());
    _lanes.push_back(*newLane);
    
    Log("Lane with Id: " + to_string(newLane->getID()));
    
    return newLane;
}

CLane* CEngine::GetLane(int id)
{
    vector<CLane>::iterator it = _lanes.begin();
    for(;it != _lanes.end(); it++)
    {
        if(it->getID() == id)
            return &*it;
    }
    
    return nullptr;
}

int CEngine::GetNumberOfVehicles()
{
    return _vehicles.size();
}

CVehicle* CEngine::GetVehicle(int id)
{
    vector<CVehicle>::iterator it = _vehicles.begin();
    
    
    for(;it != _vehicles.end();it++)
    {
        if(it->getID() == id)
            return &*it;
    }
    
    return nullptr;
}

string* CEngine::getValue()
{
    return new string("Dude from cpp");
}

vector<CVehicle> CEngine::GetAllVehicles(float deltaTime)
{
    
    vector<CVehicle>::iterator it = _vehicles.begin();
    
    CPosition* updatedPosition;
    
    for(;it != _vehicles.end(); it++)
    {
        updatedPosition = GetVehiclesCurrentPosition(&*it, deltaTime);
        it->Position = updatedPosition;
    }
    
    return _vehicles;
}

void CEngine::MoveVehicle(int x, int y, CVehicle *vehicle)
{
    vehicle->Position->setX(x);
    vehicle->Position->setY(y);
}

CPosition* CEngine::GetVehiclesCurrentPosition(CVehicle* vehicle, float deltaTime)
{
    CPosition* position = vehicle->Position;
    
    float speed = vehicle->getSpeed();

    
    position->setY(position->getY() - (speed*deltaTime));
    
    float lateralSpeed = 200;
    
    /*if(vehicle->GoalLane != nullptr) {
        CPosition* goalLanePosition = vehicle->GoalLane->Position;
        float deltaX = abs(goalLanePosition->getX() - position->getX());
        
        if(deltaX < 3)
            position->setX(goalLanePosition->getX());
        
        if(position->getX() > goalLanePosition->getX())
            position->setX(position->getX() - (lateralSpeed * deltaTime));
        else if(position->getX() < goalLanePosition->getX())
            position->setX(position->getX() + (lateralSpeed * deltaTime));
    }*/

    
    return position;
}

void CEngine::AddVehicle(CVehicle* vehicle)
{
    _vehicles.push_back(*vehicle);
}

CVehicle* CEngine::GetNewVehicle(CLane* starterLane)
{
    int type = random() % 3;
    string* carType;
    
    switch(type) {
        case 0:
            carType = new string("GreenCar");
            break;
        case 1:
            carType = new string("RedCar");
            break;
        case 2:
            carType = new string("BlueCar");
            break;
    }
    
    CVehicle* vehicle = new CVehicle(this->getNextCarId(), carType, type);
    
    vehicle->GoalLane = starterLane;
    vehicle->Position->setX(starterLane->Position->getX());
    vehicle->Position->setY(480);
    
    this->AddVehicle(vehicle);
    
    //logFunction(new string("delegate writing........."));
    //Log("testing");
    Log("Starting new car in lane " + to_string(vehicle->GoalLane->getID()));
    Log("Starting cordinates x: " + to_string(vehicle->Position->getX()) + " y: " + to_string(vehicle->Position->getY()));
    return vehicle;
}

void CEngine::Log(string message)
{
    if(logFunction != nullptr)
        logFunction(message);
    else
        cout << "Internal logging: " << message << "\n";
}

void CEngine::ExecuteMethod(void (*func)())
{
    func();
}

int CEngine::getNextCarId()
{
    _carIdCounter = _carIdCounter + 1;
    return _carIdCounter;
}

int CEngine::getNextLaneId()
{
    _laneIdCounter = _laneIdCounter + 1;
    return _laneIdCounter;
}

void CEngine::RemoveVehicle(CVehicle* vehicleToRemove)
{
    for(vector<CVehicle>::iterator it = _vehicles.begin(); it != _vehicles.end(); it++)
    {
        it->getID();
        if(it->getID() == vehicleToRemove->getID())
        {
            _vehicles.erase(it);
            break;
        }
    }
    
    /*for(int i = 0; i < _vehicles->size(); i++)
    {
        CVehicle currentVehicle = _vehicles->at(i);
        
        if(vehicleToRemove->getID() == currentVehicle.getID())
        {
            break;
        }
    }*/
}
