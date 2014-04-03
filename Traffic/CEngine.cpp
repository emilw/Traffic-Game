//
//  CEngine.cpp
//  Traffic
//
//  Created by Emil Westholm on 2014-03-09.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#include "CEngine.h"

CEngine::CEngine(void (*printOutFunc) (string), CEnginePlugin* plugin)
{
    logFunction = printOutFunc;
    _gameOver = false;
    _enginePlugin = plugin;
}

CLane* CEngine::GetNewLane(Color color)
{
    CLane* newLane = new CLane(this->getNextLaneId(), color);
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

float CEngine::GetUpdatedDeltaTimeInSeconds()
{
    //Get the time poninter to now
    auto now = std::chrono::system_clock::now();
    
    //Get the duration from epoch time point to now
    auto duration = now.time_since_epoch();
    
    //Use the duration object to calculate the milliseconds from epoch to now
    auto timestampNow = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    
    
    //cout << "milisecs: " << timestampNow << std::endl;
    
    double deltaTime = 0;
    
    //Check if it's the first run
    if(_lastTimestampMilliseconds != 0)
    {
        deltaTime = timestampNow - _lastTimestampMilliseconds;
    }
    
    //Convert the delta time to seconds
    double deltaTimeSecs = deltaTime;
    
    deltaTimeSecs = deltaTimeSecs/1000.0000000;
    
    cout << "secs: " << deltaTimeSecs << std::endl;
    
    //Update the latest time stamp to now, for the next run
    _lastTimestampMilliseconds = timestampNow;
    
    return deltaTimeSecs;
}

vector<CVehicle> CEngine::GetAllVehicles()
{
    double deltaTime = this->GetUpdatedDeltaTimeInSeconds();
    
    //deltaTime = deltaT;
    
    printf("delta time: %f \n", deltaTime);
    
    //float deltaT = 0;
    
    /*if(_lastTimestamp != 0)
    {
        deltaT = timeStampNow - _lastTimestamp;
        
        printf("%f timestampnow, last timestamp %f, delta %f", timeStampNow, _lastTimestamp, deltaT);
    }*/
    
    _remainingTime = _remainingTime - deltaTime;
    
    
    vector<CVehicle>::iterator it = _vehicles.begin();
    
    CPosition* updatedPosition;
    
    for(;it != _vehicles.end(); it++)
    {
        _enginePlugin->PreUpdateVehicle(&*it);
        
        updatedPosition = GetVehiclesCurrentPosition(&*it, deltaTime);
        it->Position = updatedPosition;
        
        //Mark the vehicle to be removed
        if(!it->IsToBeRemoved() && it->EndOfTheRoad())
        {
            it->MarkToBeRemoved();
            
            //If the car leaves the road with
            if(it->Color == it->CurrentLane->Color)
            {
                AddExtraTime();
            }
            Log("Car left the road end");
        }
        else if(it->IsToBeRemoved())
        {
            int id = it->getID();
            _vehicles.erase(it);
            _enginePlugin->PostRemoveVehicle(id);
            Log("Car was removed");
        }
        
        
        //Check collision with all vehicles
        vector<CVehicle>::iterator otherVehicleIterator = _vehicles.begin();
        for(;otherVehicleIterator != _vehicles.end();otherVehicleIterator++)
        {
            if(it->getID() == otherVehicleIterator->getID())
                continue;
            
            if(it->IsCollision(&*otherVehicleIterator))
            {
                this->GameOver(GameOverReason::CRASH);
                break;
            }
        }
        
        _enginePlugin->PostUpdateVehicle(&*it);
    }
    
    
    if(_remainingTime < 0)
    {
        this->GameOver(GameOverReason::TIME);
    }
    
    return _vehicles;
}

/*void CEngine::MoveVehicle(int x, int y, CVehicle *vehicle)
{
    vehicle->Position->setX(x);
    vehicle->Position->setY(y);
}*/

CPosition* CEngine::GetVehiclesCurrentPosition(CVehicle* vehicle, float deltaTime)
{
    CPosition* position = vehicle->Position;
    
    float speed = vehicle->getSpeed();

    
    position->setY(position->getY() - (speed*deltaTime));
    
    float lateralSpeed = 200;
    
    if(vehicle->CurrentLane != nullptr) {
        CPosition* goalLanePosition = vehicle->CurrentLane->Position;
        float deltaX = std::abs(goalLanePosition->getX() - position->getX());
    
        if(deltaX < 3)
            position->setX(goalLanePosition->getX());
        
        if(position->getX() > goalLanePosition->getX())
            position->setX(position->getX() - (lateralSpeed * deltaTime));
        else if(position->getX() < goalLanePosition->getX())
            position->setX(position->getX() + (lateralSpeed * deltaTime));
        
        
        Log("Engine - Goal lane position x: " + to_string(goalLanePosition->getX()) + ", y: " + to_string(goalLanePosition->getY()));
    }

    
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
    Color color;
    switch(type) {
        case 0:
            carType = new string("GreenCar");
            color = Color::GREEN;
            break;
        case 1:
            carType = new string("RedCar");
            color = Color::RED;
            break;
        case 2:
            carType = new string("BlueCar");
            color = Color::BLUE;
            break;
    }
    
    CVehicle* vehicle = new CVehicle(this->getNextCarId(), color);
    
    vehicle->CurrentLane = starterLane;
    vehicle->Position->setX(starterLane->Position->getX());
    vehicle->Position->setY(480);
    
    this->AddVehicle(vehicle);
    
    //logFunction(new string("delegate writing........."));
    //Log("testing");
    Log("Starting new car in lane " + to_string(vehicle->CurrentLane->getID()));
    Log("Starting cordinates x: " + to_string(vehicle->Position->getX()) + " y: " + to_string(vehicle->Position->getY()));
    
    //Test
    _enginePlugin->PostNewVehicle(vehicle);
    
    
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
}

void CEngine::GameOver(GameOverReason reason)
{
    _gameOver = true;
    _enginePlugin->GameOver(reason);
}

bool CEngine::IsGameOver()
{
    return _gameOver;
}

void CEngine::StartGame()
{
    
}

void CEngine::AddExtraTime()
{
    _remainingTime = _remainingTime + 2;
}

float CEngine::GetRemainingTime()
{
    return _remainingTime;
}
