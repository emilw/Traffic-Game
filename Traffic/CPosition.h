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
    int x;
    int y;
public:
    CPosition(int x = 0, int y = 0) { x = x; y = y;};
    int getX();
    int getY();
    void setY(int value);
    void setX(int value);
};

#endif /* defined(__Traffic__CPosition__) */
