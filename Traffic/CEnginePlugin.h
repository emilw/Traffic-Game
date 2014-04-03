//
//  EnginePlugin.h
//  Traffic
//
//  Created by Emil Westholm on 2014-03-31.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#ifndef __Traffic__CEnginePlugin__
#define __Traffic__CEnginePlugin__

#include <iostream>
#include "CVehicle.h"
#include "SharedEnum.h"

class CEnginePlugin
{
public:
    CEnginePlugin(void* fascadeObject);
    virtual void PreUpdateVehicle(CVehicle* vehicle);
    virtual void PostUpdateVehicle(CVehicle* vehicle);
    virtual void GameOver(GameOverReason reason);
    virtual void PostNewVehicle(CVehicle* vehicle);
    virtual void PostRemoveVehicle(int id);
    void* _fascadeObject;
private:
};


#endif /* defined(__Traffic__CEnginePlugin__) */
