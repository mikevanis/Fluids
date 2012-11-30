//
//  Vector.cpp
//  Fluids
//
//  Created by Michail Vanis on 25/11/2012.
//
//

#include "VectorPoint.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "cinder/app/AppBasic.h"

using namespace ci;

VectorPoint::VectorPoint() {
    
}

VectorPoint::VectorPoint(Vec2f location, Vec2f direction, float strength) {
    loc = location;
    dir = direction;
    str = strength;
    arrowLength = 15.0f;
    headLength = 6.0f;
    headRadius = 3.0f;
}

void VectorPoint::update() {
    
}

// Convert Vec2f to Vec3f and draw arrow
void VectorPoint::draw() {
    Vec3f drawLoc(loc, 0.0f);
    Vec3f drawDir(dir, 0.0f);
    gl::color(Color(0.2f, 0.2f, 0.2f));
    gl::drawVector(drawLoc, drawLoc + drawDir * arrowLength, headLength, headRadius);
}

void VectorPoint::setDirection(Vec2f direction) {
    dir = direction;
}

// Return vector's normalized direction
Vec2f VectorPoint::getDirection() {
    return dir;
}

// Return vector's acceleration influence
float VectorPoint::getStrength() {
    return str;
}