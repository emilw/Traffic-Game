//
//  CLane.cpp
//  Traffic
//
//  Created by Emil Westholm on 2014-03-26.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#include "CLane.h"

CLane::CLane(int id, enum Color color)
{
    _id = id;
    Position = new CPosition();
    Color = color;
}

int CLane::getID()
{
    return _id;
}