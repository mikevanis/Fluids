//
//  VectorPoint.h
//  Fluids
//
//  Created by Michail Vanis on 25/11/2012.
//
//

#ifndef Fluids_VectorPoint_h
#define Fluids_VectorPoint_h

#pragma once
#include "cinder/Vector.h"

#include <vector>

class VectorPoint {
public:
    VectorPoint();
    VectorPoint(ci::Vec2f location, ci::Vec2f direction, float strength);
    void update();
    void draw();
    void setDirection(ci::Vec2f direction);
    
    ci::Vec2f getDirection();
    float getStrength();
    
    ci::Vec2f loc;
    ci::Vec2f dir;
    float str;
    
    float arrowLength, headLength, headRadius, zoneLength;
};

#endif