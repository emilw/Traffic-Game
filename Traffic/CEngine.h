//
//  CEngine.h
//  Traffic
//
//  Created by Emil Westholm on 2014-03-09.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#ifndef __Traffic__CEngine__
#define __Traffic__CEngine__

#include <iostream>
#include <vector>
#include <cmath>
//#include <ctime>
#include <chrono>
#include "CVehicle.h"
#include "CPosition.h"
#include "CLane.h"
#include "CEnginePlugin.h"
#include "SharedEnum.h"

using namespace std;

class CEngine
{
public:
    
    CEngine(void (*printOutFunc) (string), CEnginePlugin* enginePlugin);
    CEngine(){};
    
    //Internal
    string* getValue();
    CEnginePlugin* _enginePlugin;
    
    
    //Variables
    vector<CVehicle> _vehicles;
    vector<CLane> _lanes;
    
    //Lane methods
    CLane* GetNewLane(Color color);
    CLane* GetLane(int id);
    
    //Vehicle methods
    void AddVehicle(CVehicle* vehicle);
    void RemoveVehicle(CVehicle* vehicle);
    vector<CVehicle> GetAllVehicles();
    CVehicle* GetNewVehicle(CLane* starterLane);
    CPosition* GetVehiclesCurrentPosition(CVehicle* vehicle, float deltaTime);
    //void MoveVehicle(int x, int y, CVehicle* vehicle);
    int GetNumberOfVehicles();
    CVehicle* GetVehicle(int id);
    
    //Game methods
    bool IsGameOver();
    void StartGame();
    void GameOver(GameOverReason reason);
    float GetRemainingTime();
    
    //Dummy tests
    void ExecuteMethod(void (*func)());
    void Log(string message);
    //float _lastTimestamp = 0;
    
private:
    int _carIdCounter = 0;
    int _laneIdCounter = 0;
    float _remainingTime = 20;
    //Milliseconds
    long long _lastTimestampMilliseconds = 0;
    //long _lastTimestamp = 0;
    //std::chrono::steady_clock::time_point _lastTimestamp;
    
    int getNextCarId();
    int getNextLaneId();
    bool _gameOver;
    void (*logFunction) (string);
    
    //Internal engine methods
    float GetUpdatedDeltaTimeInSeconds();
    void AddExtraTime();

};

#endif /* defined(__Traffic__CEngine__) */
