//
//  Quadrant.cpp
//  Fluids
//
//  Created by Michail Vanis on 12/12/2012.
//
//

#include "Quadrant.h"

using namespace ci;

Quadrant::Quadrant(VectorPoint *v1, VectorPoint *v2, VectorPoint *v3, VectorPoint *v4) {
    vector1 = v1;
    vector2 = v2;
    vector3 = v3;
    vector4 = v4;
}

Vec2f Quadrant::getAverageDirection(Vec2f location) {
    
}

bool Quadrant::isInQuadrant(Vec2f location) {
    
}