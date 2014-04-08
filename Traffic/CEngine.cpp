//
//  CEngine.cpp
//  Traffic
//
//  Created by Emil Westholm on 2014-03-09.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#include "CEngine.h"

CEngine::CEngine(void (*printOutFunc) (string), CEnginePlugin* plugin, float screenWidth, float screenHeight)
{
    logFunction = printOutFunc;
    _screenWidth = screenWidth;
    _screenHeight = screenHeight;
    _gameOver = false;
    _enginePlugin = plugin;
}

CLane* CEngine::GetNewLane(Color color, float x)
{
#warning Should not be hard coded sizes, should be height according to the screen height and screen width / 3
    CLane* newLane = new CLane(this->getNextLaneId(), color, 60, _screenHeight, x);
    _lanes.push_back(*newLane);
    
    string message;
    
    message = message + "Lane added with Id: " + to_string(newLane->getID());
    message = message + " and width/height(" + to_string(newLane->Size->GetWidth()) + "/" + to_string(newLane->Size->GetHeight()) + ")";
    message = message + " x/y(" + to_string(newLane->Position->getX()) + "/" + to_string(newLane->Position->getY()) + ")";

    Log(message);
    
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

long long CEngine::GetTimestamp()
{
    //Get the time poninter to now
    auto now = std::chrono::system_clock::now();
    
    //Get the duration from epoch time point to now
    auto duration = now.time_since_epoch();
    
    //Use the duration object to calculate the milliseconds from epoch to now
    return std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

float CEngine::GetUpdatedDeltaTimeInSeconds()
{
    auto timestampNow = GetTimestamp();
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

float CEngine::GetTotalTime()
{
    return _totalTime;
}

vector<CVehicle> CEngine::GetAllVehicles()
{
    
    double deltaTime = this->GetUpdatedDeltaTimeInSeconds();
    
    _totalTime = _totalTime + deltaTime;
    
    printf("delta time: %f \n", deltaTime);
    
    _remainingTime = _remainingTime - deltaTime;
    
    
    vector<CVehicle>::iterator it = _vehicles.begin();
    
    CPosition* updatedPosition;
    
    
    _vehicleArrayLock.lock();
    for(;it != _vehicles.end(); it++)
    {
        //Due to the screen updating thread is the main thread, we need to call the screen from the main thread and not the thread creating new vehicles
        if(it->IsNew())
        {
            _enginePlugin->PostNewVehicle(&*it);
            it->TurnOfIsNew();
        }
        else
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
                Log("Vehicle " + to_string(it->getID()) + " left the road end");
            }
            else if(it->IsToBeRemoved())
            {
                int id = it->getID();
                _vehicles.erase(it);
                _enginePlugin->PostRemoveVehicle(id);
                Log("Vehicle " + to_string(it->getID()) + " was removed");
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
    }
    
    _vehicleArrayLock.unlock();
    
    
    if(_remainingTime < 0)
    {
        this->GameOver(GameOverReason::TIME);
    }
    
    
    return _vehicles;
}

void CEngine::MoveVehicle(int x, int y, CVehicle *vehicle)
{
    vehicle->Move(x, y);
 
    _vehicleArrayLock.lock();
    vector<CLane>::iterator it = _lanes.begin();
 
    for(;it != _lanes.end(); it++)
    {
        if(it->IsInFrame(x,y))
        {
            Log("Vehicle " + to_string(vehicle->getID()) + " moved to lane " + to_string(it->getID()));
            vehicle->CurrentLane = &*it;
            break;
        }
        
    }
    
    _vehicleArrayLock.unlock();
}

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
        
        
        Log("Current lane position x: " + to_string(goalLanePosition->getX()) + ", y: " + to_string(goalLanePosition->getY()));
    }

    
    return position;
}

void CEngine::AddVehicle(CVehicle* vehicle)
{
    _vehicles.push_back(*vehicle);
}

void CEngine::StartNewVehicle(CLane* starterLane)
{
    string carType;
    
    Color color = this->getRandomColor();
    
    CVehicle* vehicle = new CVehicle(this->getNextCarId(), color, 58, 65);
    
    vehicle->CurrentLane = starterLane;
    vehicle->Position->setX(starterLane->Position->getX());
    vehicle->Position->setY(starterLane->Size->GetHeight());
    
    Log("Starting new car in lane " + to_string(vehicle->CurrentLane->getID()));
    Log("Starting cordinates x: " + to_string(vehicle->Position->getX()) + " y: " + to_string(vehicle->Position->getY()));
    
    _vehicleArrayLock.lock();
    this->AddVehicle(vehicle);
    
    _enginePlugin->PostNewVehicle(vehicle);
    _vehicleArrayLock.unlock();
}

void CEngine::Log(string message)
{
    if(logFunction != nullptr)
        logFunction(message);
    else
        cout << "Internal logging: " << message << "\n";
}

int CEngine::getNextCarId()
{
    _vehicleCounterLock.lock();
    _carIdCounter = _carIdCounter + 1;
    _vehicleCounterLock.unlock();
    return _carIdCounter;
}

int CEngine::getNextLaneId()
{
    _laneCounterLock.lock();
    _laneIdCounter = _laneIdCounter + 1;
    _laneCounterLock.unlock();
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

void CEngine::AddExtraTime()
{
    _remainingTime = _remainingTime + 2;
}

float CEngine::GetRemainingTime()
{
    return _remainingTime;
}

CLane* CEngine::GetRandomLane()
{
    Color color = getRandomColor();
    
    vector<CLane>::iterator it = _lanes.begin();
    for(;it != _lanes.end(); it++)
    {
        if(it->Color == color)
            return &*it;
    }
    
    return nullptr;
}

Color CEngine::getRandomColor()
{
    int type = random() % 3;
    Color color;
    switch(type) {
        case 0:
            color = Color::GREEN;
            break;
        case 1:
            color = Color::RED;
            break;
        case 2:
            color = Color::BLUE;
            break;
    }
    
    return color;
}

void CEngine::CarStarter(CEngine* engine)
{
    //int i = 0;
    
    int randomStartIntervall = 0;
    while(true)
    {
        if(engine->IsGameOver() || engine->IsPaused())
            break;
        
        CLane* lane = engine->GetRandomLane();
        engine->StartNewVehicle(lane);
        
        randomStartIntervall = random() % 1000+ 600;
        std::chrono::milliseconds dura(randomStartIntervall);
        std::this_thread::sleep_for(dura);
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
    _carStarter = new thread(CarStarter, this);
}

void CEngine::Resume()
{
    _lastTimestampMilliseconds = GetTimestamp();
    _paused = false;
    _carStarter = new thread(CarStarter, this);
}

void CEngine::Pause()
{
    _paused = true;
}

bool CEngine::IsPaused()
{
    return _paused;
}
