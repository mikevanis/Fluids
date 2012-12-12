//
//  Quadrant.h
//  Fluids
//
//  Created by Michail Vanis on 12/12/2012.
//
//

#ifndef Fluids_Quadrant_h
#define Fluids_Quadrant_h

#pragma once

#include "cinder/Vector.h"
#include "VectorPoint.h"

class Quadrant {
public:
    Quadrant();
    Quadrant(VectorPoint *v1, VectorPoint *v2, VectorPoint *v3, VectorPoint *v4);
    bool isInQuadrant(ci::Vec2f location);
    ci::Vec2f getAverageDirection(ci::Vec2f location);
    
    VectorPoint *vector1;
    VectorPoint *vector2;
    VectorPoint *vector3;
    VectorPoint *vector4;
};

#endif
