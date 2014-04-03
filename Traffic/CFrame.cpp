//
//  CFrame.cpp
//  Traffic
//
//  Created by Emil Westholm on 2014-04-03.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#include "CFrame.h"

CFrame::CFrame()
{
    this->Position = new CPosition(0,0);
}

bool CFrame::IsInFrame(float x, float y)
{
    if(this->GetX1() < x &&
       this->GetX2() > x &&
       this->GetY1() < y &&
       this->GetY2() > y)
        return true;
    return false;
}

bool CFrame::IsCollision(CFrame *otherFrame)
{
    //Get the cordinates for the otherVehicle
    if(otherFrame->GetX1() < this->GetX2() &&
       otherFrame->GetX2() > this->GetX1() &&
       otherFrame->GetY1() < this->GetY2() &&
       otherFrame->GetY2() > this->GetY1()){
        return true;
    }
    
    return false;
}


float CFrame::GetX1()
{
    return this->Position->getX() - (this->Size->GetWidth()/2);
}

float CFrame::GetX2()
{
    return this->Position->getX() + (this->Size->GetWidth()/2);
}

float CFrame::GetY1()
{
    return this->Position->getY() - (this->Size->GetHeight()/2);
}

float CFrame::GetY2()
{
    return this->Position->getY() + (this->Size->GetHeight()/2);
}