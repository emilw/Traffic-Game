//
//  CFrame.h
//  Traffic
//
//  Created by Emil Westholm on 2014-04-03.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#ifndef __Traffic__CFrame__
#define __Traffic__CFrame__

#include <iostream>
#include "CPosition.h"
#include "CSize.h"

class CFrame
{
public:
    CFrame();
    CPosition* Position;
    CSize* Size;
    
    
    bool IsCollision(CFrame* otherFrame);
    bool IsInFrame(float x, float y);
    
    //Cordinates methods
    float GetX1();
    float GetX2();
    float GetY1();
    float GetY2();
};

#endif /* defined(__Traffic__CFrame__) */
