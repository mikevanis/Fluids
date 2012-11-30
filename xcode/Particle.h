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
#include "cinder/Vector.h"

#include <vector>

class Particle {
public:
    Particle();
    Particle(ci::Vec2f location);
    Particle(ci::Vec2f location, ci::Vec2f destination, float velocity);
    void update();
    void draw();
    void setVector(ci::Vec2f destination, float velocity);
    
    ci::Vec2f loc;
    ci::Vec2f dir;
    float vel;
    float acc;
    
    float radius;
};

#endif
