//
//  Tracking.hpp
//  MicroCosmos
//
//  Created by Oscar Nord on 2017-04-25.
//
//
#ifndef Tracking_hpp
#define Tracking_hpp

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Capture.h"
#include "cinder/gl/Texture.h"
#include "cinder/Log.h"
#include "cinder/Utilities.h"

#include "CinderOpenCV.h"
#include "../src/aruco/src/cvdrawingutils.h"
#include "../src/aruco/src/cameraparameters.h"

class Tracking {
public:
    void setup();
    void update();
    void draw();
    
    //get position of markers from id
    glm::vec3 getPosMarker(const int &id);
    //convert camera coordinates to screen coordinates
    glm::vec2 getScreenCoordinates(glm::vec3 markerPos);
    
private:
    aruco::CameraParameters cam_param_;
    aruco::CameraParameters cam_param_update_;
    aruco::MarkerDetector marker_detector_;
    std::vector<aruco::Marker> markers_;
    
    ci::CaptureRef capture_;
    ci::Surface surf_;
    ci::gl::TextureRef texture_;
    cv::Mat input_;
    const int cornerpos_ = 2; //0, 1, 2
    std::map<int, std::vector<double>> marker_map_;

    //corners of the screen in camera coordinates
    //p0 is (0,0) on screen, p1 is (1,0) and p2 is (0,1)
    glm::vec3 p0_, p1_, p2_;
    //vectors that makes calculations easier
    glm::vec3 normX_, normY_;
    //size of marker, this needs to change if a new markersize is used (calibration)
    const float kMarker_size_ = 0.075f;
    const std::string kVR_labCamera_ = "Logitech Webcam C930e";
    
    //check for connected devices
    void printDevices();
    //get position of cornermarkers
    std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> getCornerPos();
    //save camera coordinates for screen corners
    void setCorners();
};

#endif /* Tracking_hpp */
