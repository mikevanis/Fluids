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

#define MINVELOCITY 0.05f

Particle::Particle() {

}

// Random velocity and destination
Particle::Particle(Vec2f location) {
    loc = location;
    dir = Vec2f(0, 1);
    vel = 0.2f;
    radius = 3.0f;
    acc = 0;
    timer = 100;
}

// Predetermined velocity and destination
Particle::Particle(Vec2f location, Vec2f destination, float velocity) {
    loc = location;
    dir = destination;
    vel = velocity;
    acc = 0.02f;
    radius = 3.0f;
}

void Particle::update(const Channel32f &channel) {
    if(channel) {
        float gray = channel.getValue(loc);
        acc = mapValue(gray, 1.0f, 0.0f, 0.2f, -0.2);
    }
    vel += acc;
    
    if(vel<=0.05) loc += dir * 0.05;
    else loc += dir * vel;
    
    timer -= 0.5f;
}

void Particle::draw() {
    gl::color(Color(0.4, 0.4, 1));
    gl::drawSolidCircle(loc, radius * (timer/100));
}

bool Particle::isDead() {
    if(timer <= 0.0f) {
        return true;
    }
    else {
        return false;
    }
}

// Range mapping function (ported from Arduino) ----------------------------
float Particle::mapValue(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x-in_min) * (out_max-out_min) / (in_max-in_min) + out_min;
}