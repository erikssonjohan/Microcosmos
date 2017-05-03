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

//TODO: DONT DO IT THIS WAY AT RELEASE
//get position of specific arucomarkers (cornerpoints)
std::tuple<vector<double>, vector<double>, vector<double>> Tracking::getCornerPos() {
    std::map<int, vector<double>>::iterator it0;
    std::map<int, vector<double>>::iterator it1;
    std::map<int, vector<double>>::iterator it2;

    it0 = _markerMap.find(1);
    it1 = _markerMap.find(2);
    it2 = _markerMap.find(3);
    return std::make_tuple(it0->second,it1->second,it2->second);
}

//Save camera coordinates for the corners of the screen
void Tracking::setCorners() {
    auto corners = getCornerPos();
    auto P0 = std::get<0>(corners);
    auto P1 = std::get<1>(corners);
    auto P2 = std::get<2>(corners);

    //lazy check if we have the first markers
    if (!P0.empty() && !P1.empty() && !P2.empty()) {
        for (auto t = std::make_tuple(P0.begin(), P1.begin(), P2.begin(), 0);
             std::get<0>(t) != P0.end() && std::get<1>(t) != P1.end() && std::get<2>(t) != P2.end() && std::get<3>(t) <= cornerpos;
             ++std::get<0>(t), ++std::get<1>(t), ++std::get<2>(t), std::get<3>(t)++) {
            
            p0[std::get<3>(t)] = *std::get<0>(t);
            p1[std::get<3>(t)] = *std::get<1>(t);
            p2[std::get<3>(t)] = *std::get<2>(t);
        }
        normX = glm::normalize(p1 - p0);
        normY = glm::normalize(p2 - p0);
        //cout << "normX: " << normX << " normY: " << normY <<  endl;
    }
}

vec3 Tracking::getPosMarker(const int &id){
    std::map<int, vector<double>>::iterator it0;
    it0 = _markerMap.find(id);
    vec3 pos = {0,0,0};
    vec3 negVec = {-1, -1, -1};
    if(it0->second.empty()){
        return negVec;
    }
    else{
        for( auto t = std::make_tuple(it0->second.begin(), 0); std::get<0>(t) != it0->second.end();
            ++std::get<0>(t), std::get<1>(t)++){
            pos[std::get<1>(t)] = * std::get<0>(t);
        }
        return pos;
    }
}



//Returns Screen coordinates between 0 and 1
vec2 Tracking::getScreenCoordinates(vec3 markerPos) {
    vec3 x = glm::dot((markerPos - p0), normX)*normX /glm::length(p1-p0);
    vec3 y = glm::dot((markerPos - p0), normY)*normY /glm::length(p2-p0);
    vec2 result = {glm::length(x),glm::length(y)};
    //If it is not between 0 and 1 it is wrong! Try dividing with length of X and Y
    cout << "TEST: " << result << endl;
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
    
    static bool firsttime = true;

    
    if( !mCapture || !mCapture->checkNewFrame())
        return;
    
    if(!mTexture) {
        // Capture images
        mTexture = gl::Texture::create(*mCapture->getSurface(), gl::Texture::Format().loadTopDown());
        mSurf = Surface(Channel8u(mTexture->createSource()));
    }

    //Read in update-loop due to resize() every frame
    //mCamParam.readFromXMLFile("/Users/DavidTran/Documents/LinkopingUniversitetSkola/TNM094-Kandidat/GitHub/camera_results.yml");
    mCamParam.readFromXMLFile("/Users/oscar/Documents/TNM094-Media-navigering/MicroCosmos/assets/camera_results.yml");

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
        cout << "ID: " << it.first << endl;
        for(auto it2 = it.second.begin(); it2 != it.second.end(); ++it2)
            cout << " POS: " << "[ " << *it2 << " ]"<< endl;
    }
    
    if (_markerMap.count(1) > 0 && _markerMap.count(2) > 0 && _markerMap.count(3) > 0 && firsttime) {
        firsttime = false;
        setCorners();
        _markerMap.erase(1);
        _markerMap.erase(2);
        _markerMap.erase(3);
        cout << "hejhej" << p0;
    }
    cout << "Size: " << _markerMap.size() << endl;
}


void Tracking::draw() {
    gl::enableAlphaBlending();
    gl::color( ColorA(1,1,1,1.0f) );

    if( mTexture ) {
        gl::draw( mTexture );
    }
}
