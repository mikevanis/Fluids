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
using namespace std;

#define MINVELOCITY 0.05f
#define HISTORY 50
#define STEP 10

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
    
    currentStep = 0;
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
        acc = mapValue(gray * 0.75, 1.0f, 0.0f, 0.2f, -0.2);
    }
    vel += acc;
    vel *= 0.98;
    
    if(vel<=0.05) loc += dir * 0.05;
    else loc += dir * vel;
    
    timer -= 0.5f;
    
    prevLocations.push_back(loc);
    
    // Store point to point queue
    if(prevLocations.size() >= HISTORY) {
        prevLocations.erase(prevLocations.begin());
    }
}

void Particle::draw() {
    gl::color(Color(0.4, 0.4, 1));
    //gl::drawSolidCircle(loc, radius * (timer/100));
    
    int counter = 0;
    
    // Draw point array
    for(vector<Vec2f>::iterator v = prevLocations.begin(); v != prevLocations.end(); ++v) {
        if(counter % STEP == currentStep) {
            gl::drawSolidCircle(*v, 1);
        }
        
        counter++;
    }
    
    currentStep++;
    if(currentStep >= STEP) currentStep = 0;
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