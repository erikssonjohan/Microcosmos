//
//  VirtualCard.hpp
//  MicroCosmos
//
//  Created by Oscar Nord on 2017-04-21.
//
//

#ifndef VirtualCard_hpp
#define VirtualCard_hpp
#include <stdio.h>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "poNodeContainer.h"
#include "poShape.h"
#include "cinder/Rand.h"
using namespace ci;
using namespace ci::app;
using namespace std;

class VirtualCard;
typedef std::shared_ptr<VirtualCard> VirtualCardRef;

class VirtualCard
: public po::scene::NodeContainer
{
public:
    
    static VirtualCardRef create(ci::Color color, std::string path, float scale, std::vector<std::string> categories, std::string header_se, std::string text_se, std::string header_en, std::string text_en);
    void setup(ci::Color color);
    
    VirtualCard(std::string path, float scale, std::vector<std::string> categories, std::string header_se, std::string text_se, std::string header_en, std::string text_en );
    
    float x, y;
    
protected:
    
private:
    po::scene::ShapeRef mBaseShape;
    ci::vec2            mBasePosition;
    ci::Color           mBaseColor;
    std::vector<uint32_t> touchId;
    
    
    float radAngle = 0.0f;
    std::string _path;
    float _scale;
    std::vector<std::string> _categories;
    std::string _header_se;
    std::string _text_se;
    std::string _header_en;
    std::string _text_en;
    
    
    //gl::Texture2dRef mTex;
    
    
    //	Keep track of the initial, start and end position to use for dragging
    ci::vec2 mStartPos, mEndPos, mInitialPos;
    
    void removeTouchId(uint32_t id);
    bool idInCard(uint32_t id);
    
    
    //	Keep track on pressed for dragging
    bool mIsPressed;
    
    void onTouchDown(po::scene::TouchEvent &event);
    
    //	Touch dragged event handler
    void onTouchDragged(po::scene::TouchEvent &event);
    
    //	Touch up event handler
    void onTouchUp(po::scene::TouchEvent &event);
    
    
    
};




#endif /* VirtualCard_hpp */

