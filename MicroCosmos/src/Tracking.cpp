//
//  Tracking.cpp
//  MicroCosmos
//
//  Created by Oscar Nord on 2017-04-25.
//
//

#include "Tracking.hpp"
#include <iostream>

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
    const auto corners = getCornerPos();
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
    }
}

glm::vec3 Tracking::getPosMarker(const int &id) {
    std::map<int, vector<double>>::iterator it0;
    it0 = _markerMap.find(id);
    glm::vec3 pos = {0,0,0};
    glm::vec3 negVec = {-1, -1, -1};
    if(it0 == _markerMap.end()) {
        return negVec;
    }
    else{
        for(auto t = std::make_tuple(it0->second.begin(), 0);
            std::get<0>(t) != it0->second.end(); ++std::get<0>(t), std::get<1>(t)++) {
            
            pos[std::get<1>(t)] = * std::get<0>(t);
        }
        return pos;
    }
}


//Returns Screen coordinates between 0 and 1
glm::vec2 Tracking::getScreenCoordinates(glm::vec3 markerPos) {
    glm::vec3 x = glm::dot((markerPos - p0), normX)*normX /glm::length(p1-p0);
    glm::vec3 y = glm::dot((markerPos - p0), normY)*normY /glm::length(p2-p0);
    glm::vec2 result = {glm::length(x),glm::length(y)};
    
    //If it is not between 0 and 1 it is wrong! Try dividing with length of X and Y
    return glm::vec2(glm::length(x),glm::length(y));
}


void Tracking::printDevices() {
    for(const auto &device : ci::Capture::getDevices()) {
        ci::app::console() << "Device: " << device->getName() << " " << endl;
    }
}


void Tracking::setup() {

    //print cameras and init camera capture
    printDevices();
    try {
        mCapture = ci::Capture::create(640, 480);
        mCapture->start();
    }
    catch( ci::Exception &exc ) {
        CI_LOG_EXCEPTION("Failed to init capture", exc);
        exit(1);
    }
}


void Tracking::update() {
    static bool firsttime = true;

    if(!mCapture || !mCapture->checkNewFrame()) {
        return;
    }
    
    if(!mTexture) {
        // Capture images
        mTexture = ci::gl::Texture::create(*mCapture->getSurface(), ci::gl::Texture::Format().loadTopDown());
        mSurf = ci::Surface(ci::Channel8u(mTexture->createSource()));
    }

    //TODO: Fix this at release
    //Read in update-loop due to resize() every frame
    //mCamParam.readFromXMLFile("/Users/DavidTran/Documents/LinkopingUniversitetSkola/TNM094-Kandidat/GitHub/camera_results.yml");
    mCamParam.readFromXMLFile("/Users/oscar/Documents/TNM094-Media-navigering/MicroCosmos/assets/camera_results.yml");
    
    mTexture->update(*mCapture->getSurface());
    input = toOcv(ci::Surface(ci::Channel8u(mTexture->createSource())));
    mCamParam.resize(input.size());
    mMarkerDetector.detect(input, mMarkers, mCamParam, 0.028f);
    
    for (auto i : mMarkers) {
        double pos[3];
        double rot[4];
        
        i.OgreGetPoseParameters(pos, rot);
        std::map<int, vector<double>>::iterator iter;
        iter = _markerMap.begin();
        if (iter == _markerMap.end())
            _markerMap.insert(pair<int,vector<double>>(i.id,{pos[0],pos[1],pos[2]}));
        else
            _markerMap[i.id] = {pos[0],pos[1],pos[2]};
    }
   
    //print markerinfo
 /* for (const auto it : _markerMap) {
        std::cout << "ID: " << it.first << std::endl;
        for(auto it2 = it.second.begin(); it2 != it.second.end(); ++it2)
            std::cout << " POS: " << "[ " << *it2 << " ]"<< std::endl;
    } */
    
    //Check for cornermarkers
    if (_markerMap.count(1) > 0 && _markerMap.count(2) > 0 && _markerMap.count(3) > 0 && firsttime) {
        firsttime = false;
        setCorners();
        _markerMap.erase(1);
        _markerMap.erase(2);
        _markerMap.erase(3);
    }
}


void Tracking::draw() {
    ci::gl::enableAlphaBlending();
    ci::gl::color( ci::ColorA(1,1,1,1.0f) );

    if( mTexture ) {
        ci::gl::draw( mTexture );
    }
}
