//
//  EnginePlugin.cpp
//  Traffic
//
//  Created by Emil Westholm on 2014-03-31.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#include "CEnginePlugin.h"

CEnginePlugin::CEnginePlugin(void* fascadeObject)
{
    _fascadeObject = fascadeObject;
}

void CEnginePlugin::PreUpdateVehicle(CVehicle* vehicle)
{
    cout << "Default PreUpdateVehicle call, should be overloaded";
}


void CEnginePlugin::PostUpdateVehicle(CVehicle *vehicle)
{
    cout << "Default PostUpdateVehicle call, should be overloaded";
}

void CEnginePlugin::GameOver(GameOverReason reason)
{
    cout << "Default GameOver call, should be overloaded";
}

void CEnginePlugin::PostNewVehicle(CVehicle *vehicle)
{
    cout << "Default PostNewCar call, should be overloaded";
}

void CEnginePlugin::PostRemoveVehicle(int id)
{
    cout << "Default PostRemoveVehicle call, should be overloaded";
}