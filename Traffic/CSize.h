//
//  CSize.h
//  Traffic
//
//  Created by Emil Westholm on 2014-03-30.
//  Copyright (c) 2014 Emil Westholm. All rights reserved.
//

#ifndef __Traffic__CSize__
#define __Traffic__CSize__

#include <iostream>

class CSize
{
private:
    float _height;
    float _width;
public:
    CSize(float width, float height) {_height = height; _width = width;}
    float GetHeight();
    float GetWidth();
};

#endif /* defined(__Traffic__CSize__) */
