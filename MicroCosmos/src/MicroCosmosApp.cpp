#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Capture.h"
#include "cinder/gl/Texture.h"
#include "cinder/Log.h"
#include "cinder/Xml.h"
#include "CinderOpenCV.h"

#include "poScene.h"
#include "MicroCosmos.hpp"
#include "ParticleController.h"

#pragma warning( disable : 4290 )

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace po::scene;

class MicroCosmosApp : public App {
public:
    void setup() override;
    void keyDown(KeyEvent event) override;
    void update() override;
    void draw() override;
    //po
    po::scene::SceneRef scene;
    ParticleController mParticles;
};


void prepareSettings(MicroCosmosApp::Settings *settings) {
    settings->setMultiTouchEnabled( true );
    settings->setFullScreen(true);
}

void MicroCosmosApp::setup() {
    // cinder::app::setFullScreen();
    scene = Scene::create(MicroCosmos::create());
    //Create particles at random locations and give them a velocity
    mParticles.setup();

    getSignalUpdate().connect( [this](){
        getWindow()->setTitle(to_string((int)getAverageFps())+" fps");
    });
}


void MicroCosmosApp::keyDown(KeyEvent event) {
    if (event.getChar() == 'f') {
        // Toggle full screen when the user presses the 'f' key.
        setFullScreen(!isFullScreen());
    }
    else if (event.getCode() == KeyEvent::KEY_ESCAPE) {
        // Exit full screen, or quit the application, when the user presses the ESC key.
        if (isFullScreen())
            setFullScreen(false);
        else
            quit();
    }
}


void MicroCosmosApp::update() {
    //update scene
    scene->update();
    //update particles
    mParticles.update();
}


void MicroCosmosApp::draw() {
    gl::clear(Color(0, 0, 0));
    mParticles.draw();
    scene->draw();
    
    // Draw yellow circles at the active touch points
    gl::color(1, 1, 0);
    for (const auto &touch : getActiveTouches()) {
        gl::drawStrokedCircle(touch.getPos(), 20);
    }
}

CINDER_APP( MicroCosmosApp, RendererGl, prepareSettings )
