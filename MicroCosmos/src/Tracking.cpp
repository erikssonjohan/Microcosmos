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

//get position of specific arucomarker
vector<double> Tracking::getCornerPos() {
    //set marker
    std::map<int, vector<double>>::iterator it = _markerMap.find(1);
    return it->second;
}


//Save camera coordinates for the corners of the screen
void Tracking::setCorners(vec3 P0, vec3 P1, vec3 P2) {
    p0 = P0; p1 = P1; p2 = P2;
    normX = normalize(p1 - p0);
    normY = normalize(p2-p0);
}


//Returns Screen coordinates between 0 and 1
vec2 Tracking::getScreenCoordinates(vec3 markerPos) {
    vec3 x = glm::dot((markerPos - p0), normX)*normX; // /glm::length(p1-p0);
    vec3 y = glm::dot((markerPos - p0), normY)*normY; // /glm::length(p2-p0);
    
    //If it is not between 0 and 1 it is wrong! Try dividing with legth of X and Y
    return vec2(glm::length(x),glm::length(y));
}


void Tracking::printDevices() {
    for( const auto &device : Capture::getDevices() ) {
        console() << "Device: " << device->getName() << " " << endl;
    }
}


void Tracking::calibration() {
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
        // Capture images
        mTexture = gl::Texture::create(*mCapture->getSurface(), gl::Texture::Format().loadTopDown());
        mSurf = Surface(Channel8u(mTexture->createSource()));
    }

    //Read in update-loop due to resize() every frame
    mCamParam.readFromXMLFile("/Users/oscar/Documents/TNM094-Media-navigering/MicroCosmos/assets/camera_results.yml");
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
        map<int, vector<double>>::iterator iter;
        iter = _markerMap.begin();
        if (iter == _markerMap.end())
            _markerMap.insert(pair<int,vector<double>>(i.id,{pos[0],pos[1],pos[2]}));
        else
            _markerMap[i.id] = {pos[0],pos[1],pos[2]};
    }
    
    for (const auto it : _markerMap) {
        cout << "ID: " << it.first;
        for(auto it2 = it.second.begin(); it2 != it.second.end(); ++it2)
            cout << " POS: " << "[ " << *it2 << " ]"<< endl;
    }
    cout << "Size: " << _markerMap.size();
}


void Tracking::draw() {
    gl::enableAlphaBlending();
    gl::color( ColorA(1,1,1,1.0f) );

    if( mTexture ) {
        gl::draw( mTexture );
    }
}
