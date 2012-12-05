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
#include <iostream>
#include <fstream>
#include <math.h>

#define MAXPARTICLES 300

using namespace ci;
using std::list;
using namespace std;

ParticleController::ParticleController() {}

ParticleController::ParticleController(int res) {
    mXRes = app::getWindowWidth()/res;
    mYRes = app::getWindowHeight()/res;
    
    // Add vectors
    for (int y=0; y<mYRes; y++) {
        for(int x=0; x<mXRes; x++) {
            Vec2f direction = Vec2f(0, 1);
            app::console() << "Vector:" << direction << std::endl;
            addVector(Vec2f(x, y), direction, res);
        }
    }
    lastFrames = 0;
    app::console() << "Vectors added" << std::endl;
}

// Update particles --------------------------------------------------------
void ParticleController::update(Vec2i mouseLoc, bool settingMode, bool selectedVector, bool selectedDir, const Channel32f &channel) {
    unsigned long currentFrames = app::getElapsedFrames();
    if(settingMode) {
        if(!selectedVector && !selectedDir) {
            currentVector = getVectorOnLocation(mouseLoc);
        }
        else if(selectedVector && !selectedDir) {
            dirToCursor = mouseLoc - currentVector->loc;
            dirToCursor.safeNormalize();
            currentVector->dir = dirToCursor;
        }
    }
    app::console() << currentFrames-lastFrames << std::endl;
    if(autoParticles) {
        if(currentFrames-lastFrames >= 50) {
            if(particleList.size() < MAXPARTICLES) {
                for(int x=0; x<mXRes; x++) {
                    addParticle(x*30, 10);
                }
            }
            lastFrames = currentFrames;
        }
    }
    
    for(list<Particle>::iterator p=particleList.begin(); p != particleList.end(); ++p) {
        p->update(channel);
        if(p->isDead()) particleList.erase(p);
    }
}

// Draw vector map and particles -------------------------------------------
void ParticleController::draw() {
    for(list<VectorPoint>::iterator v=vectorList.begin(); v!= vectorList.end(); ++v) {
        v->draw();
    }
    for(list<Particle>::iterator p=particleList.begin(); p != particleList.end(); ++p) {
        p->draw();
    }
}

// Apply vector map influence to particles ----------------------------------
void ParticleController::applyForces() {
    for(list<Particle>::iterator p = particleList.begin(); p != particleList.end(); ++p) {
        for(list<VectorPoint>::iterator v = vectorList.begin(); v != vectorList.end(); ++v) {
            Vec2f dir = p->loc - v->loc;
            float distSqrd = dir.lengthSquared();
            float zoneRadiusSqrd = v->zoneLength * v->zoneLength;
            if(distSqrd <= zoneRadiusSqrd) {
                p->dir = v->dir;
            }
        }
    }
}

// Add a single particle to the particle list ------------------------------
void ParticleController::addParticle(int xi, int yi) {
    particleList.push_back(Particle(Vec2f(xi, yi)));
}

// Add a single vector to the vector list ----------------------------------
void ParticleController::addVector(Vec2f location, Vec2f direction, int res) {
    float x = (location.x+0.5f) * (float)res;
    float y = (location.y+0.5f) * (float)res;
    VectorPoint newVector = VectorPoint(Vec2f(x, y), direction, 1.0f);
    newVector.zoneLength = res/2;
    vectorList.push_back(newVector);
}

// Add particles in random locations ---------------------------------------
void ParticleController::addParticles(int amt) {
    for(int i=0; i<amt; i++) {
        float x = Rand::randFloat(app::getWindowWidth());
        float y = Rand::randFloat(app::getWindowHeight());
        particleList.push_back(Particle(Vec2f(x, y)));
    }
}

// Remove a specified amount of particles ----------------------------------
void ParticleController::removeParticles(int amt) {
    for(int i=0; i<amt; i++) {
        particleList.pop_back();
    }
}

// Range mapping function (ported from Arduino) ----------------------------
float ParticleController::mapValue(float x, float in_min, float in_max, float out_min, float out_max) {
    return (x-in_min) * (out_max-out_min) / (in_max-in_min) + out_min;
}

// Find vector nearest to a location ---------------------------------------
VectorPoint* ParticleController::getVectorOnLocation(Vec2i &position) {
    VectorPoint* foundVector;
    for(list<VectorPoint>::iterator v = vectorList.begin(); v != vectorList.end(); ++v) {
        Vec2f *dir = new (std::nothrow) Vec2f(position - v->loc);
        float distSqrd = dir->lengthSquared();
        float zoneRadiusSqrd = v->zoneLength * v->zoneLength;
        if(distSqrd <= zoneRadiusSqrd) {
            foundVector = &*v;
            break;
        }
        delete dir;
        dir = NULL;
    }
    return foundVector;
}

void ParticleController::saveListToFile(list<VectorPoint> mList, string fileName) {
    ofstream mFile;
    mFile.open(fileName.c_str());
    for(list<VectorPoint>::iterator v= mList.begin(); v != mList.end(); ++v) {
        if(mFile.is_open()) {
            mFile << v->loc.x << ",";
            mFile << v->loc.y << ",";
            mFile << v->dir.x << ",";
            mFile << v->dir.y << ",";
            mFile << v->str << ",";
            mFile << v->arrowLength << ",";
            mFile << v->zoneLength << ",";
            mFile << v->headLength << ",";
            mFile << v->headRadius << "\n";
        }
    }
    app::console() << "Saved file " << fileName << std::endl;
    mFile.close();
}

void ParticleController::openListFromFile(string fileName) {
    vectorList.clear();
    string line;
    ifstream mFile;
    
    mFile.open(fileName.c_str());
    if(mFile.is_open()) {
        while(mFile.good()) {
            getline(mFile, line);
            
            // Parsing
            int comma1 = line.find(',', 0);
            int comma2 = line.find(',', comma1+1);
            int comma3 = line.find(',', comma2+1);
            int comma4 = line.find(',', comma3+1);
            int comma5 = line.find(',', comma4+1);
            int comma6 = line.find(',', comma5+1);
            int comma7 = line.find(',', comma6+1);
            int comma8 = line.find(',', comma7+1);
            
            VectorPoint newVector;
            newVector.loc.x = atof(line.substr(0, comma1).c_str());
            newVector.loc.y = atof(line.substr(comma1+1, comma2).c_str());
            newVector.dir.x = atof(line.substr(comma2+1, comma3).c_str());
            newVector.dir.y = atof(line.substr(comma3+1, comma4).c_str());
            newVector.str = atof(line.substr(comma4+1, comma5).c_str());
            newVector.arrowLength = atof(line.substr(comma5+1, comma6).c_str());
            newVector.zoneLength = atof(line.substr(comma6+1, comma7).c_str());
            newVector.headLength = atof(line.substr(comma7+1, comma8).c_str());
            newVector.headRadius = atof(line.substr(comma8+1, line.length()).c_str());
            
            vectorList.push_back(newVector);
        }
    }
}