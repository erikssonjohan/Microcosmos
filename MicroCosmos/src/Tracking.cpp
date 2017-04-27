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
        
        //execl("/Users/oscar/Downloads/aruco-2.0.19/cmake-build-debug/utils_calibration/aruco_calibration", "aruco_calibration", "live", "camera_results.yml", "-size", "0.034", "-m", "/Users/oscar/Downloads/aruco-2.0.19/cmake-build-debug/utils_calibration/aruco_calibration_board_a4.yml", (char*)0);
        
        perror("execl() failure!\n\n");

    }
    
    else if(press == 'N') {
        cout << "Continue with program.." << endl;
    }
    else{
        cout << "Invalid character" << endl;
    }
}

void Tracking::setup() {

    //print cameras and init camera capture
    printDevices();
    //calibration();
    try {
        mCapture = Capture::create( 640, 480 );
        mCapture->start();
    }
    catch( ci::Exception &exc ) {
        CI_LOG_EXCEPTION( "Failed to init capture ", exc );
        exit(1);
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

    //Read in update-loop due to resize() every frame
    //mCamParam.readFromXMLFile("/Users/oscar/Documents/TNM094-Media-navigering/MicroCosmos/assets/camera_results.yml");
    //mCamParam.readFromXMLFile("/Users/oscar/Documents/TNM094-Media-navigering/MicroCosmos/assets/camera_results.yml");

    mTexture->update(*mCapture->getSurface());
    input = toOcv(Surface(Channel8u(mTexture->createSource())));
    mCamParam.resize(input.size());

    //aruco::MarkerDetector mMarkerDetector;
    mMarkerDetector.detect(input, mMarkers, mCamParam, 0.028f);
    for (auto i : mMarkers) {
        double pos[3];
        double rot[4];
        i.OgreGetPoseParameters(pos, rot);
        _markerMap.insert(pair<int,vector<double>>(i.id,{pos[0],pos[1],pos[2]}));
        for (const auto t : _markerMap) {
            cout << "ID: " << t.first << " POS: ";
            for(auto it2 = t.second.begin(); it2 != t.second.end(); ++it2)
                cout << *it2 << endl;
        }
    }
}


void Tracking::draw() {

    gl::enableAlphaBlending();
    gl::color( ColorA(1,1,1,1.0f) );

    if( mTexture ) {
        gl::draw( mTexture );
    }
}
