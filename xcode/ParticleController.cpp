//
//  ParticleController.cpp
//  Fluids
//
//  Created by Michail Vanis on 19/11/2012.
//
//

#include "ParticleController.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "iostream"

using namespace ci;
using std::list;

ParticleController::ParticleController() {}

ParticleController::ParticleController(int res) {
    mXRes = app::getWindowWidth()/res;
    mYRes = app::getWindowHeight()/res;
    
    // Add vectors
    for (int y=0; y<mYRes; y++) {
        for(int x=0; x<mXRes; x++) {
            float xi = mapValue(x, 0, mXRes, 0, -1);
            float yi = mapValue(y, 0, mYRes, 1, -1);
            
            Vec2f direction = Vec2f(xi, yi);
            direction.safeNormalize();
            
            app::console() << "Vector:" << direction << std::endl;
            
            addVector(Vec2f(x, y), direction, res);
        }
    }
    app::console() << "Vectors added" << std::endl;
    
    // Add particles
    /*
    for(int i=0; i<20; i++) {
        addParticle(i*100+50, 600);
    }*/
    //addParticle(200, 200);
}

// Update particles
void ParticleController::update() {
    for(list<Particle>::iterator p=particleList.begin(); p != particleList.end(); ++p) {
        p->update();
    }
}

// Draw vector map and particles
void ParticleController::draw() {
    for(list<VectorPoint>::iterator v=vectorList.begin(); v!= vectorList.end(); ++v) {
        v->draw();
    }
    for(list<Particle>::iterator p=particleList.begin(); p != particleList.end(); ++p) {
        p->draw();
    }
}

// Apply vector map influence to particles
void ParticleController::applyForces() {
    for(list<Particle>::iterator p = particleList.begin(); p != particleList.end(); ++p) {
        for(list<VectorPoint>::iterator v = vectorList.begin(); v != vectorList.end(); ++v) {
            Vec2f dir = p->loc - v->loc;
            float distSqrd = dir.lengthSquared();
            float zoneRadiusSqrd = v->arrowLength * v->arrowLength;
            if(distSqrd <= zoneRadiusSqrd) {
                p->setVector(v->dir, 3.0f);
            }
        }
    }
}

// Add a single particle to the particle list
void ParticleController::addParticle(int xi, int yi) {
    particleList.push_back(Particle(Vec2f(xi, yi)));
}

// Add a single vector to the vector list
void ParticleController::addVector(Vec2f location, Vec2f direction, int res) {
    float x = (location.x+0.5f) * (float)res;
    float y = (location.y+0.5f) * (float)res;
    vectorList.push_back(VectorPoint(Vec2f(x, y), direction, 1.0f));
}

// Add particles in random locations
void ParticleController::addParticles(int amt) {
    for(int i=0; i<amt; i++) {
        float x = Rand::randFloat(app::getWindowWidth());
        float y = Rand::randFloat(app::getWindowHeight());
        particleList.push_back(Particle(Vec2f(x, y)));
    }
}

// Remove a specified amount of particles
void ParticleController::removeParticles(int amt) {
    for(int i=0; i<amt; i++) {
        particleList.pop_back();
    }
}

// Range mapping function (ported from Arduino)
float ParticleController::mapValue(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x-in_min) * (out_max-out_min) / (in_max-in_min) + out_min;
}