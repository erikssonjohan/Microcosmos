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
    
private:
    //aruco
    void printDevices();
    aruco::CameraParameters mCamParam;
    aruco::MarkerDetector mMarkerDetector;
    vector<aruco::Marker> mMarkers;
    
    CaptureRef mCapture;
    Surface mSurf;
    gl::TextureRef mTexture;
};


void MicroCosmosApp::printDevices()
{
    for( const auto &device : Capture::getDevices() ) {
        console() << "Device: " << device->getName() << " " << endl;
    }
}


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
    
    //print cameras and init camera capture
    printDevices();
    try {
        mCapture = Capture::create( 640, 480 );
        mCapture->start();
    }
    catch( ci::Exception &exc ) {
        CI_LOG_EXCEPTION( "Failed to init capture ", exc );
    }
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
    
    //aruco
    if( mCapture && mCapture->checkNewFrame()) {
        if(!mTexture) {
            // Capture images come back as top-down, and it's more efficient to keep them that way
            mTexture = gl::Texture::create(*mCapture->getSurface(), gl::Texture::Format().loadTopDown());
            mSurf = Surface(Channel8u(mTexture->createSource()));
        }
        else {
            mTexture->update(*mCapture->getSurface());
            cv::Mat input = toOcv(Surface(Channel8u(mTexture->createSource())));
            mMarkerDetector.detect(input, mMarkers);
        }
    }
}

void MicroCosmosApp::draw()
{
    
    gl::clear( Color( 0, 0.5, 0 ) );
    scene->draw();
    
    // Draw yellow circles at the active touch points
    gl::color( 1, 1, 0 );
    for( const auto &touch : getActiveTouches
        () ){
        gl::drawStrokedCircle( touch.getPos(), 20 );
    }
    
    
    /*
    gl::enableAlphaBlending();
    gl::color( ColorA(1,1,1,1.0f) );
    
    if( mTexture ) {
        gl::draw( mTexture );
    }
    
    gl::color( ColorA(1,1,1,0.7f) );
    
    double pos[3];
    double rot[4];
    
    for( int i=0; i<mMarkers.size(); i++) {
        
        for( int ii = 0; ii < mMarkers[i].size(); ii++){
          gl::drawSolidCircle(vec2(mMarkers[i][ii].x, mMarkers[i][ii].y), 10.0f);
            std::cout << "Marker x: " << mMarkers[i][ii].x << " Marker y: " << mMarkers[i][ii].y << endl;
        
        }
        
        
        //mMarkers[i].OgreGetPoseParameters(pos, rot);
        //cout << "Pos " << "x: " << pos[1] << " y: "  << pos[2] << " z: " << pos[3] << endl;
        //cout << mMarkers[i].id << endl;
        //gl::drawSolidCircle(vec2(pos[1],pos[2]), 10.0f);
    }
    */
}

CINDER_APP( MicroCosmosApp, RendererGl, prepareSettings )
