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
#include "CVehicle.h"
#include "CPosition.h"
#include "CLane.h"

using namespace std;

class CEngine
{
public:
    CEngine(void (*printOutFunc) (string)){logFunction = printOutFunc;};
    CEngine(){};
    string* getValue();
    vector<CVehicle> _vehicles;
    vector<CLane> _lanes;
    
    //Lane methods
    CLane* GetNewLane();
    CLane* GetLane(int id);
    
    //Vehicle methods
    void AddVehicle(CVehicle* vehicle);
    void RemoveVehicle(CVehicle* vehicle);
    vector<CVehicle> GetAllVehicles(float deltaTime);
    CVehicle* GetNewVehicle(CLane* starterLane);
    CPosition* GetVehiclesCurrentPosition(CVehicle* vehicle, float deltaTime);
    void MoveVehicle(int x, int y, CVehicle* vehicle);
    
    int GetNumberOfVehicles();
    CVehicle* GetVehicle(int id);
    
    //Dummy tests
    void ExecuteMethod(void (*func)());
    void Log(string message);
    float _lastTimestamp = 0;
    
private:
    int _carIdCounter = 0;
    int _laneIdCounter = 0;
    int getNextCarId();
    int getNextLaneId();
    void (*logFunction) (string);

};

#endif /* defined(__Traffic__CEngine__) */
