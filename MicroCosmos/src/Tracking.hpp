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
#include "aruco/src/cvdrawingutils.h"
#include "aruco/src/cameraparameters.h"

class Tracking {
public:
    void setup();
    void update();
    void draw();
    void printDevices();
    std::tuple<std::vector<double>, std::vector<double>, std::vector<double>> getCornerPos();
    //save camera coordinates for screen corners
    void setCorners();
    glm::vec3 getPosMarker(const int &id);
    //convert camera coordinates to screen coordinates
    glm::vec2 getScreenCoordinates(glm::vec3 markerPos);
    
private:
    aruco::CameraParameters mCamParam;
    aruco::MarkerDetector mMarkerDetector;
    std::vector<aruco::Marker> mMarkers;
    
    ci::CaptureRef mCapture;
    ci::Surface mSurf;
    ci::gl::TextureRef mTexture;
    cv::Mat input;
    const int cornerpos_ = 2;
    std::map<int, std::vector<double>> markerMap;

    //corners of the screen in camera coordinates
    //p0 is (0,0) on screen, p1 is (1,0) and p2 is (0,1)
    glm::vec3 p0,p1,p2;
    //vectors that makes calculations easier
    glm::vec3 normX, normY;

};

#endif /* Tracking_hpp */
