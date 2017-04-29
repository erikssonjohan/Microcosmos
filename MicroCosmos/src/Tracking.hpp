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

#include "CinderOpenCV.h"
#include "aruco/src/cvdrawingutils.h"
#include "aruco/src/cameraparameters.h"

using namespace ci;
using namespace ci::app;
using namespace std;


class Tracking {
public:
    
    //Tracking();
    //~Tracking();
    
    void setup();
    void update();
    void draw();
    void printDevices();
    void calibration();
    std::tuple<vector<double>, vector<double>, vector<double>> getCornerPos();
    void setCorners(); //save camera coordinates for screen corners
    vec2 getScreenCoordinates(vec3 markerPos); //convert camera coordinates to screen coordinates

    
private:
    aruco::CameraParameters mCamParam;
    aruco::MarkerDetector mMarkerDetector;
    vector<aruco::Marker> mMarkers;
    
    CaptureRef mCapture;
    Surface mSurf;
    gl::TextureRef mTexture;

    cv::Mat input;

    map<int, vector<double>> _markerMap;

    
    //corners of the screen in camera coordinates
    vec3 p0,p1,p2; //p0 is (0,0) on screen, p1 is (1,0) and p2 is (0,1)
    vec3 normX, normY; //vectors that makes calculations easier

};

#endif /* Tracking_hpp */
