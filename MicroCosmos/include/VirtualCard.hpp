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
#include "poTextBox.h"
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

    //sets upp det card
    void setup(ci::Color color);

    //Constructor for the card
    VirtualCard(std::string path, float scale, std::vector<std::string> categories, std::string header_se, std::string text_se, std::string header_en, std::string text_en );
    
    float x, y;
    
protected:
    
private:

    float border = 10;



    po::scene::ShapeRef mBaseShape;
    ci::vec2            mBasePosition;
    ci::Color           mBaseColor;

    //touch vector
    std::vector<uint32_t> touchId;
    std::vector<po::scene::TouchEvent> events;
    std::vector<vec2> pPos;


    po::scene::ShapeRef textFig;
    po::scene::TextBoxRef textContent;
    
    float angle = 0.0f;
    std::string _path;
    float _scale = 0.4;
    std::vector<std::string> _categories;
    std::string _header_se;
    std::string _text_se;
    std::string _header_en;
    std::string _text_en;
    
    //	Keep track of the initial, start and end position to use for dragging
    ci::vec2 mStartPos, mEndPos, mInitialPos;

    //removes touch id from card
    void removeTouchId(uint32_t id);

    // Checks if card has the touch id
    bool idInCard(uint32_t id);

    //removes touch id from card
    void removeTouchEvent(po::scene::TouchEvent tEvent);

    //	Keep track on pressed for dragging
    bool mIsPressed;
    
    void onTouchDown(po::scene::TouchEvent &event);
    
    //	Touch dragged event handler
    void onTouchDragged(po::scene::TouchEvent &event);
    
    //	Touch up event handler
    void onTouchUp(po::scene::TouchEvent &event);
    
    //Scale
    void scale(ci::vec2 pos1, ci::vec2 pPos1, ci::vec2 pos2, ci::vec2 pPos2 );


    
};




#endif /* VirtualCard_hpp */

