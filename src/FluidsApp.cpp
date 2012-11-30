#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "ParticleController.h"
#include "Particle.h"
#include "VectorPoint.h"
#include "cinder/Rand.h"
#include "iostream"

#define RESOLUTION 30

using namespace ci;
using namespace ci::app;
using namespace std;

class FluidsApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void keyDown( KeyEvent event );
	void update();
	void draw();
    
    ParticleController mParticleController;
    VectorPoint mVec;
};

void FluidsApp::prepareSettings(Settings *settings) {
    settings->setWindowSize(800, 600);
    settings->setFrameRate(60.0f);
}

void FluidsApp::setup()
{
    mParticleController = ParticleController(RESOLUTION);
}

void FluidsApp::keyDown( KeyEvent event )
{
    if(event.getChar() == 'c') {
        mParticleController.particleList.clear();
    }
    else if(event.getChar() == ' ') {
        mParticleController.addParticles(60);
        app::console() << "Total particles:" << mParticleController.particleList.size() << std::endl;
    }
}

void FluidsApp::update()
{
    mParticleController.applyForces();
    mParticleController.update();
}

void FluidsApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    mParticleController.draw();
}

CINDER_APP_BASIC( FluidsApp, RendererGl )
