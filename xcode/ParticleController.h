//
//  ParticleController.h
//  Fluids
//
//  Created by Michail Vanis on 19/11/2012.
//
//

#ifndef Fluids_ParticleController_h
#define Fluids_ParticleController_h

#pragma once
#include "Particle.h"
#include "VectorPoint.h"
#include <list>

class ParticleController {
public:
    ParticleController();
    ParticleController(int res);
    void update();
    void draw();
    void applyForces();
    void addParticle(int xi, int yi);
    void addVector(ci::Vec2f location, ci::Vec2f direction, int res);
    void addParticles(int amt);
    void removeParticles(int amt);
    float mapValue(float x, float in_min, float in_max, float out_min, float out_max);
    
    std::list<Particle> particleList;
    std::list<VectorPoint> vectorList;
    
    int mXRes, mYRes;
};


#endif
