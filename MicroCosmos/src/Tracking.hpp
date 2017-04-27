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
    
private:
    aruco::CameraParameters mCamParam;
    aruco::MarkerDetector mMarkerDetector;
    vector<aruco::Marker> mMarkers;
    
    CaptureRef mCapture;
    Surface mSurf;
    gl::TextureRef mTexture;
    cv::Mat input;
};

#endif /* Tracking_hpp */
