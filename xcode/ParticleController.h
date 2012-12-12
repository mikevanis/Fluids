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
#include "Quadrant.h"
#include "cinder/app/AppBasic.h"
#include <list>

class ParticleController {
public:
    ParticleController();
    ParticleController(int res);
    
    void update(ci::Vec2i mouseLoc, bool settingMode, bool selectedVector, bool selectedDir, const ci::Channel32f &channel);
    void draw();
    void applyForces();
    void applyQuadrantForces();
    void addParticle(int xi, int yi);
    void addVector(ci::Vec2f location, ci::Vec2f direction, int res);
    void addParticles(int amt);
    void removeParticles(int amt);
    void createQuadrantsFromVectors(int res);
    
    float mapValue(float x, float in_min, float in_max, float out_min, float out_max);
    VectorPoint* getVectorOnLocation(ci::Vec2i &position);
    VectorPoint* getVectorOnLocation(int x, int y, int res);
    
    void saveListToFile(std::list<VectorPoint> mList, std::string fileName);
    void openListFromFile(std::string fileName);
    
    std::list<Particle> particleList;
    std::list<VectorPoint> vectorList;
    std::list<Quadrant> quadrantList;
    
    int mXRes, mYRes;
    int vectorRes;
    
    unsigned long lastFrames;
    
    bool autoParticles = false;
    
    VectorPoint* currentVector;
    ci::Vec2f dirToCursor;
};


#endif
