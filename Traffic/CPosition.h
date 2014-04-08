//
//  CPosition.h
//  Traffic
//
//  Created by Emil Westholm on 2014-03-27.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#ifndef __Traffic__CPosition__
#define __Traffic__CPosition__

#include <iostream>

class CPosition
{
private:
    float x;
    float y;
public:
    CPosition(int x = 0, int y = 0) { this->x = x; this->y = y;};
    float getX();
    float getY();
    void setY(float value);
    void setX(float value);
};

#endif /* defined(__Traffic__CPosition__) */
