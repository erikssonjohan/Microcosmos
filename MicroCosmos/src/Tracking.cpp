//
//  Tracking.cpp
//  MicroCosmos
//
//  Created by Oscar Nord on 2017-04-25.
//
//

#include "Tracking.hpp"
#include <iostream>


using namespace ci;
using namespace ci::app;
using namespace std;


void Tracking::printDevices() {
    for( const auto &device : Capture::getDevices() ) {
        console() << "Device: " << device->getName() << " " << endl;
    }
}

void Tracking::calibration(){
    char press;
    cout << "Calibration: y/N" << endl;
    cin >> press;
    if(press == 'y'){
        cout << "YES" << endl;
        
        execl("/Users/DavidTran/Documents/LinkopingUniversitetSkola/TNM094-Kandidat/aruco-2.0.19/cmake-build-debug/utils_calibration/aruco_calibration", "-live", "camera_results.yml", "-size", "0.034", "-m", "aruco_calibration_board_a4.yml", (char *)NULL);
      
    }
    else if(press == 'N') {
        cout << "Continue with program.." << endl;
    }
    else{
        cout << "Invalid character" << endl;
    }
}

void Tracking::readYML(){
    bool check = false;
    
    //mCamParam.readFromXMLFile("Path to YML");
}

void Tracking::setup() {
    //print cameras and init camera capture
    printDevices();
    calibration();
    try {
        mCapture = Capture::create( 640, 480 );
        mCapture->start();
        
        
    }
    catch( ci::Exception &exc ) {
        CI_LOG_EXCEPTION( "Failed to init capture ", exc );
    }
}


void Tracking::update() {
    if( !mCapture || !mCapture->checkNewFrame())
        return;
    
    if(!mTexture) {
        // Capture images come back as top-down, and it's more efficient to keep them that way
        mTexture = gl::Texture::create(*mCapture->getSurface(), gl::Texture::Format().loadTopDown());
        mSurf = Surface(Channel8u(mTexture->createSource()));
    }
    
    mTexture->update(*mCapture->getSurface());
    //cv::Mat input = toOcv(Surface(Channel8u(mTexture->createSource())));
    //mCamParam.resize(input.size());
    //mMarkerDetector.detect(input, mMarkers, mCamParam, 0.028f);
}


void Tracking::draw() {
    double pos[3];
    double rot[4];

    gl::enableAlphaBlending();
    gl::color( ColorA(1,1,1,1.0f) );

    if( mTexture ) {
        gl::draw( mTexture );
    }

    for(int i=0; i<mMarkers.size(); i++) {
        gl::color(ColorA(i*0.02,i*0.08,i*0.08,0.7f));

        mMarkers[i].OgreGetPoseParameters(pos, rot);
        cout << "MarkerId " << mMarkers[i].id << endl;
        cout << "Pos " << "X: " << pos[1] << " Y: "  << pos[2] << " Z: " << pos[3] << endl;
        cout << "Center: " << mMarkers[i].getCenter() << endl;

        for( int ii = 0; ii < mMarkers[i].size(); ii++) {
            gl::drawSolidCircle(vec2(mMarkers[i][ii].x, mMarkers[i][ii].y), 10.0f);
            std::cout << "Marker x: " << mMarkers[i][ii].x << " Marker y: " << mMarkers[i][ii].y << " Marker y: " << endl;
        }
        gl::drawSolidCircle(vec2(pos[1],pos[2]), 10.0f);
    }
}
