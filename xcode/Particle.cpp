//
//  Particle.cpp
//  Fluids
//
//  Created by Michail Vanis on 19/11/2012.
//
//

#include "Particle.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"
#include <vector>

using namespace ci;

Particle::Particle() {

}

// Random velocity and destination
Particle::Particle(Vec2f location) {
    loc = location;
    dir = Vec2f(0, -1);
    vel = 0.2f;
    radius = 3.0f;
    acc = 0.1f;
}

// Predetermined velocity and destination
Particle::Particle(Vec2f location, Vec2f destination, float velocity) {
    loc = location;
    dir = destination;
    vel = velocity;
    acc = 0.02f;
    radius = 3.0f;
}

void Particle::update() {
    //vel += acc;
    loc += dir * vel;
}

void Particle::draw() {
    glColor3f(1, 0, 1);
    gl::drawSolidCircle(loc, radius);
}

void Particle::setVector(Vec2f direction, float velocity) {
    dir = direction;
    vel = velocity;
}