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
#include "aruco/src/cvdrawingutils.h"
#include "aruco/src/cameraparameters.h"
#include "Tracking.hpp"

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
    //tracking
    Tracking mTrack;
};


void prepareSettings( MicroCosmosApp::Settings *settings )
{
    // By default, multi-touch is disabled on desktop and enabled on mobile platforms.
    // You enable multi-touch from the SettingsFn that fires before the app is constructed.
    settings->setMultiTouchEnabled( true );
}

void MicroCosmosApp::setup()
{
    // cinder::app::setFullScreen();
    scene = Scene::create(MicroCosmos::create());
    //search for and start camerafeed
    mTrack.setup();

    getSignalUpdate().connect( [this](){
        getWindow()->setTitle( to_string( (int) getAverageFps() ) + " fps" );
    } );
}


void MicroCosmosApp::keyDown(KeyEvent event)
{
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


void MicroCosmosApp::update()
{
    //update scene
    scene->update();
    //update tracking
    mTrack.update();
}

void MicroCosmosApp::draw()
{
    gl::clear(Color(0, 0.5, 0));
    scene->draw();

    // Draw yellow circles at the active touch points
    gl::color(1, 1, 0);
    for (const auto &touch : getActiveTouches()) {
        gl::drawStrokedCircle(touch.getPos(), 20);
    }

    //display output from camera
    mTrack.draw();
    
    auto mType = mTrack.getCornerPos();
    for(auto i = mType.begin(); i != mType.end(); i++)
        cout << "GetFunction: " << *i << endl;
    

}

CINDER_APP( MicroCosmosApp, RendererGl, prepareSettings )
