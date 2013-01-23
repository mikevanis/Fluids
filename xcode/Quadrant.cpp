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

void Quadrant::draw() {
    gl::color(1, 1, 1);
    gl::drawStrokedRect(Rectf(vector1->loc.x, vector1->loc.y, vector4->loc.x, vector4->loc.y));
}

Vec2f Quadrant::getAverageDirection(Vec2f location) {
    Vec2f dir1 = location - vector1->loc;
    Vec2f dir2 = location - vector2->loc;
    Vec2f dir3 = location - vector3->loc;
    Vec2f dir4 = location - vector4->loc;
    
    float dist1 = dir1.lengthSquared();
    float dist2 = dir2.lengthSquared();
    float dist3 = dir3.lengthSquared();
    float dist4 = dir4.lengthSquared();
    
    float totalDist = dist1 + dist2 + dist3 + dist4;
    
    Vec2f averageDirection = vector1->dir*(1-dist1/totalDist)
        + vector2->dir*(1-dist2/totalDist)
        + vector3->dir*(1-dist3/totalDist)
        + vector4->dir*(1-dist4/totalDist);
    
    averageDirection.safeNormalize();
    
    return averageDirection;
}

bool Quadrant::isInQuadrant(Vec2f location) {
    if(location.x >= vector1->loc.x && location.x < vector4->loc.x && location.y >= vector1->loc.y && location.y < vector4->loc.y) {
        return true;
    }
    else {
        return false;
    }
}