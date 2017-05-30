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
std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> Tracking::getCornerPos() {
    return std::make_tuple(marker_map_.find(1)->second,
                           marker_map_.find(2)->second,
                           marker_map_.find(3)->second);
}


//Internal function to save camera coordinates for the corners of the screen
void Tracking::setCorners() {
    const auto kCorners = getCornerPos();
    auto P0 = std::get<0>(kCorners);
    auto P1 = std::get<1>(kCorners);
    auto P2 = std::get<2>(kCorners);

	//Values in meters of the screen and corner marker, since they cant be placed in screen coord (0,0),(1,0) and (0,1)
	//markers 
	float SCREEN_LENGTH = 1.214;
	float SCREEN_HEIGHT = 0.684;
	float P0_XTRANSL = 0.295;
	float P0_YTRANSL = 0.195;

    //lazy check if we have the first markers
    if (!P0.empty() && !P1.empty() && !P2.empty()) {
        for (auto t = std::make_tuple(P0.begin(), P1.begin(), P2.begin(), 0);
             std::get<0>(t) != P0.end() && std::get<1>(t) != P1.end() && std::get<2>(t) != P2.end() && std::get<3>(t) <= cornerpos_;
             ++std::get<0>(t), ++std::get<1>(t), ++std::get<2>(t), std::get<3>(t)++) {
            
            p0_[std::get<3>(t)] = *std::get<0>(t);
            p1_[std::get<3>(t)] = *std::get<1>(t);
            p2_[std::get<3>(t)] = *std::get<2>(t);
        }
        normX_ = glm::normalize(p1_ - p0_);
        normY_ = glm::normalize(p2_ - p0_);

		//Move corners to match the screen corners
		p0_ = p0_ - P0_XTRANSL * normX_ - P0_YTRANSL * normY_;
		p1_ = p0_ + SCREEN_LENGTH*normX_;
		p2_ = p0_ + SCREEN_HEIGHT * normY_;
    }
    std::cout << "CORNERS: " << p0_ << " | " << p1_ << " | " << p2_ << std::endl;
}


//Get position of markers in camera coordinates
glm::vec3 Tracking::getPosMarker(const int &id) {
    std::map<int, std::vector<double>>::iterator it0;
    it0 = marker_map_.find(id);

    glm::vec3 pos = {0,0,0};
    glm::vec3 negVec = {-1, -1, -1};

    if(it0 == marker_map_.end()) {
        return negVec;
    }
    else{
        for(auto t = std::make_tuple(it0->second.begin(), 0);
            std::get<0>(t) != it0->second.end(); ++std::get<0>(t), std::get<1>(t)++) {
            pos[std::get<1>(t)] = *std::get<0>(t);
        }
        return pos;
    }
}


//Returns Screen coordinates between 0 and 1
glm::vec2 Tracking::getScreenCoordinates(glm::vec3 markerPos) {
    glm::vec3 x = glm::dot((markerPos - p0_), normX_) * normX_ / glm::length(p1_ - p0_);
    glm::vec3 y = glm::dot((markerPos - p0_), normY_) * normY_ / glm::length(p2_ - p0_);
    
    //1565.22 px/m height , 1613.4 px/m width for 55inch 1920x1080 16:9 
    return glm::vec2(glm::length(x)*1613.4, glm::length(y)*1565.22);
}


//Get connected Devices
void Tracking::printDevices() {
    for(const auto &device : ci::Capture::getDevices()) {
        ci::app::console() << "Device: " << device->getName() << " " << endl;
    }
}


//Setup everything
void Tracking::setup() {
    //print available devices
    printDevices();
    //get displaysize and set capture size
    ci::DisplayRef display = ci::Display::getMainDisplay();
    ci::ivec2 displaySize = display->getSize();
    ci::app::console() << "Main display size: " << displaySize << std::endl;
    
    //init capture and load calibration file
    if(ci::Capture::findDeviceByName(kVR_labCamera_)) {
        try {
            capture_ = ci::Capture::create(displaySize.x, displaySize.y, ci::Capture::findDeviceByName(kVR_labCamera_));
            capture_->start();
            string pathToFile = ci::app::getAssetPath(ci::fs::path("camera_results_logitech.yml")).string();
            cam_param_.readFromXMLFile(pathToFile);
        }
        catch( ci::Exception &exc ) {
            CI_LOG_EXCEPTION("Failed to init capture VR-lab camera", exc);
            exit(1);
        }
    }
    else {
        try {
            capture_ = ci::Capture::create(displaySize.x, displaySize.y);
            capture_->start();
            string pathToFile = ci::app::getAssetPath(ci::fs::path("camera_results.yml")).string();
            cam_param_.readFromXMLFile(pathToFile);
        }
        catch( ci::Exception &exc ) {
            CI_LOG_EXCEPTION("Failed to init capture", exc);
            exit(1);
        }
    }

    //Read camera calibration file
    //const char* kFile = "camera_results.yml";
    //string pathToFile = ci::app::getAssetPath(ci::fs::path(kFile)).string();
    //cam_param_.readFromXMLFile(pathToFile);
}


//Update loop runs every frame
void Tracking::update() {
    //First run of update()
    static bool firsttime = true;
    //Set calibration parameters from file
    cam_param_update_ = cam_param_;

    if(!capture_ || !capture_->checkNewFrame()) {
        return;
    }
    
    if(!texture_) {
        // Capture images
        texture_ = ci::gl::Texture::create(*capture_->getSurface(), ci::gl::Texture::Format().loadTopDown());
        surf_ = ci::Surface(ci::Channel8u(texture_->createSource()));
    }

    texture_->update(*capture_->getSurface());
    input_ = toOcv(ci::Surface(ci::Channel8u(texture_->createSource())));
    cam_param_update_.resize(input_.size());
	marker_detector_.detect(input_, markers_, cam_param_update_, kMarker_size_);
    
    for (auto i : markers_) {
        double pos[3];
        double rot[4];
        
        i.OgreGetPoseParameters(pos, rot);
        std::map<int, std::vector<double>>::iterator iter;
        iter = marker_map_.begin();
        if (iter == marker_map_.end())
            marker_map_.insert(pair<int, std::vector<double>>(i.id,{pos[0],pos[1],pos[2]}));
        else
            marker_map_[i.id] = {pos[0],pos[1],pos[2]};
    }

   
    //print markerinfo
    for (const auto it : marker_map_) {
        ci::app::console() << "ID: " << it.first << std::endl;
        for(auto it2 = it.second.begin(); it2 != it.second.end(); ++it2)
            ci::app::console() << " POS: " << "[ " << *it2 << " ]"<< std::endl;
    }
    
    
    //Check for cornermarkers 
    if (marker_map_.count(1) > 0 && marker_map_.count(2) > 0 && marker_map_.count(3) > 0 && firsttime) {
        firsttime = false;
        setCorners();
        marker_map_.erase(1);
        marker_map_.erase(2);
        marker_map_.erase(3);
    }
}


//Draw to screen
void Tracking::draw() {
    ci::gl::enableAlphaBlending();
    ci::gl::color(ci::ColorA(1,1,1,1.0f));

    if(texture_) {
        ci::gl::draw(texture_);
    }
}
