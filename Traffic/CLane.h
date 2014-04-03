//
//  CLane.h
//  Traffic
//
//  Created by Emil Westholm on 2014-03-26.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#ifndef __Traffic__CLane__
#define __Traffic__CLane__

#include <iostream>
#include "CPosition.h"
#include "SharedEnum.h"
class CLane
{
public:
    CLane(int id, Color color);
    int getID();
    CPosition* Position;
    const int ENDOFTHELANE = -10;
    Color Color;
private:
    int _id;
    
};
#endif /* defined(__Traffic__CLane__) */
