#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"
#include "cinder/Rand.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Channel.h"
#include "ParticleController.h"
#include "iostream"

#define RESOLUTION 40

using namespace ci;
using namespace ci::app;
using namespace std;

class FluidsApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void keyDown( KeyEvent event );
    void mouseMove(MouseEvent event);
    void mouseDown(MouseEvent event);
	void update();
	void draw();
    void saveFile();
    void readFile();
    void loadHeatImg();
    void toggleAutoParticles();
    
    ParticleController mParticleController;
    VectorPoint mVec;
    Vec2i mousePos;
    bool settingMode = false;
    bool selectedVector = false;
    bool selectedDir = false;
    bool dynamicSetting = false;
    string fileName;
    string imgName;
    bool drawImage = false;
    
    params::InterfaceGl mParams;
    
    Channel32f heatChannel;
    gl::Texture heatImg;
    
};

void FluidsApp::prepareSettings(Settings *settings) {
    settings->setWindowSize(1280, 800);
    settings->setFrameRate(60.0f);
}

void FluidsApp::setup()
{
    mParticleController = ParticleController(RESOLUTION);
    
    // Params setup
    mParams = params::InterfaceGl("Control panel", Vec2i(200, 400));
    mParams.addButton("AutoParticles", bind(&FluidsApp::toggleAutoParticles, this));
    mParams.addSeparator();
    mParams.addParam( "Set vectors", &settingMode);
    mParams.addParam("Dynamic setting", &dynamicSetting);
    mParams.addSeparator();
    mParams.addParam("File name", &fileName, "");
    mParams.addButton("Save", bind(&FluidsApp::saveFile, this));
    mParams.addButton("Load", bind(&FluidsApp::readFile, this));
    mParams.addSeparator();
    mParams.addParam("Image name", &imgName, "");
    mParams.addButton("Load image", bind(&FluidsApp::loadHeatImg, this));
    mParams.addParam( "Draw heat map", &drawImage);
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
    else if(event.getChar() == 's' && (!selectedDir || !selectedVector)) {
        settingMode = !settingMode;
        app::console() << "Setting vectors..." << std::endl;
    }
}

void FluidsApp::mouseMove(MouseEvent event) {
    mousePos = event.getPos();
}

void FluidsApp::mouseDown(MouseEvent event) {
    if(settingMode) {
        if(!selectedVector && !selectedDir) {
            app::console() << "Selecting vector." << std::endl;
            selectedDir = false;
            selectedVector = true;
        }
        else if(selectedVector && !selectedDir) {
            app::console() << "Selecting direction." << std::endl;
            selectedDir = false;
            selectedVector = false;
        }
    }
}


void FluidsApp::update()
{
    mParticleController.applyQuadrantForces();
    //mParticleController.applyForces();
    mParticleController.update(mousePos, settingMode, selectedVector, selectedDir, heatChannel);
}

void FluidsApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
    
    gl::color(Color(1, 1, 1));
    if(drawImage) {
        heatImg.enableAndBind();
        gl::draw(heatImg, getWindowBounds());
    }
    mParticleController.draw();
    
    params::InterfaceGl::draw();
}

void FluidsApp::saveFile() {
    string absPath = getAssetPath("").string() + "/topography/" + fileName;
    mParticleController.saveListToFile(mParticleController.vectorList, absPath);
}

void FluidsApp::readFile() {
    string absPath = getAssetPath("").string() + "/topography/" + fileName;
    mParticleController.openListFromFile(absPath);
}

void FluidsApp::loadHeatImg() {
    if(imgName != "") {
        DataSourceRef imgAsset;
        try {
            imgAsset = loadAsset("heat_maps/" + imgName);
            heatChannel = Channel32f(loadImage(imgAsset));
            heatImg = heatChannel;
            app::console() << "Loaded image." << std::endl;
        }
        catch (AssetLoadExc e) {
            app::console() << "File does not exist!" << std::endl;
        }
    }
}

void FluidsApp::toggleAutoParticles() {
    mParticleController.autoParticles = !mParticleController.autoParticles;
}

CINDER_APP_BASIC( FluidsApp, RendererGl )
