//
//  Particle.h
//  Fluids
//
//  Created by Michail Vanis on 19/11/2012.
//
//

#ifndef Fluids_Particle_h
#define Fluids_Particle_h

#pragma once
#include "cinder/app/AppBasic.h"
#include <vector>

class Particle {
public:
    Particle();
    Particle(ci::Vec2f location);
    Particle(ci::Vec2f location, ci::Vec2f destination, float velocity);
    void update(const ci::Channel32f &channel);
    void draw();
    bool isDead();
    float mapValue(float x, float in_min, float in_max, float out_min, float out_max);
    
    ci::Vec2f loc;
    ci::Vec2f dir;
    float vel;
    float acc;
    float timer;
    float radius;
    
    int currentStep;
    
    std::vector<ci::Vec2f> prevLocations;
};

#endif
