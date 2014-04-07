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
#include <thread>
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
    
    //Mutex/Locks
    std::mutex _vehicleArrayLock;
    std::mutex _vehicleCounterLock;
    std::mutex _laneArrayLock;
    std::mutex _laneCounterLock;
    
    //Internal
    string* getValue();
    CEnginePlugin* _enginePlugin;
    
    
    //Variables
    vector<CVehicle> _vehicles;
    vector<CLane> _lanes;
    
    //Lane methods
    CLane* GetNewLane(Color color);
    CLane* GetLane(int id);
    CLane* GetRandomLane();
    
    //Vehicle methods
    void AddVehicle(CVehicle* vehicle);
    void RemoveVehicle(CVehicle* vehicle);
    vector<CVehicle> GetAllVehicles();
    void StartNewVehicle(CLane* starterLane);
    CPosition* GetVehiclesCurrentPosition(CVehicle* vehicle, float deltaTime);
    void MoveVehicle(int x, int y, CVehicle* vehicle);
    int GetNumberOfVehicles();
    CVehicle* GetVehicle(int id);
    
    //Thread method
    static void CarStarter(CEngine* engine);
    
    //Game methods
    bool IsGameOver();
    void StartGame();
    void GameOver(GameOverReason reason);
    float GetRemainingTime();
    float GetTotalTime();
    long long GetTimestamp();
    void Resume();
    void Pause();
    bool IsPaused();
    void Log(string message);
    
private:
    int _carIdCounter = 0;
    int _laneIdCounter = 0;
    float _remainingTime = 20;
    float _totalTime = 0;
    long long _lastTimestampMilliseconds = 0;
    
    thread* _carStarter;
    
    //Internal engine methods
    int getNextCarId();
    int getNextLaneId();
    bool _gameOver;
    void (*logFunction) (string);
    Color getRandomColor();
    float GetUpdatedDeltaTimeInSeconds();
    void AddExtraTime();
    bool _paused = false;
};

#endif /* defined(__Traffic__CEngine__) */
