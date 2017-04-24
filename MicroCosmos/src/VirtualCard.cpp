//
//  VirtualCard.cpp
//  MicroCosmos
//
//  Created by Oscar Nord on 2017-04-21.
//
//

#include "VirtualCard.hpp"


#include "poShape.h"

using namespace po::scene;



VirtualCard::VirtualCard(std::string path, float scale, std::vector<std::string> categories, std::string header_se,
               std::string text_se, std::string header_en, std::string text_en)
{
    _path = path;
    _scale = scale;
    _categories = categories;
    _header_se = header_se;
    _text_se = text_se;
    _header_en = header_en;
    _text_en = text_en;
    
    
    cinder::gl::TextureRef mFrameTexture;
    cinder::gl::TextureRef texture;
    
    x = ci::Rand::randFloat(1, 800);
    y = ci::Rand::randFloat(1, 800);
    
    
}

VirtualCardRef VirtualCard::create( ci::Color color, std::string path, float scale, std::vector<std::string> categories, std::string header_se,
                         std::string text_se, std::string header_en, std::string text_en)
{
    VirtualCardRef ref (new VirtualCard(path, scale, categories, header_se,
                              text_se, header_en, text_en ));
    ref->setup(color);
    return ref;
}




void VirtualCard::setup(ci::Color color)
{
    mStartPos = ci::vec2();
    mEndPos = ci::vec2();
    mInitialPos = ci::vec2();
    mIsPressed=false;
    //  create and add the shape to the node container
    mBaseShape = Shape::createRect(500, 500);
    mBaseColor = color;
    mBaseShape->setFillColor(color);
    //mBaseShape->setRotation(45.f);
    ci::gl::TextureRef img =  ci::gl::Texture::create(ci::loadImage(ci::app::loadAsset(_path) ));
    mBaseShape->setTexture(img);
    addChild(mBaseShape);
    setName(_header_se);

    
    
    getSignal(po::scene::TouchEvent::BEGAN_INSIDE).connect(std::bind(&VirtualCard::onTouchDown, this, std::placeholders::_1));
    getSignal(po::scene::TouchEvent::MOVED_INSIDE).connect(std::bind(&VirtualCard::onTouchDragged, this, std::placeholders::_1));
    getSignal(po::scene::TouchEvent::MOVED).connect(std::bind(&VirtualCard::onTouchDragged, this, std::placeholders::_1));
    getSignal(po::scene::TouchEvent::ENDED_INSIDE).connect(std::bind(&VirtualCard::onTouchUp, this, std::placeholders::_1));
    getSignal(po::scene::TouchEvent::ENDED).connect(std::bind(&VirtualCard::onTouchUp, this, std::placeholders::_1));
    
    //  add a signal to all mouse clicks to activate label
    //getSignal(MouseEvent::DOWN_INSIDE).connect(std::bind(&Square::showIndicator, this));
    
}

void VirtualCard::onTouchDown(po::scene::TouchEvent &event){
    if (!idInCard(event.getId())) {
        std::cout << "tryck " << event.getId() << std::endl;
        mIsPressed = true;
        touchId.push_back(event.getId());
        
        // Moves the card to drawn at the front
        getParent()->moveChildToFront(getParent()->getChildByName(this->getName()));

        // Update the position of the card
        mInitialPos = getPosition();
        mStartPos = getParent()->windowToLocal(event.getWindowPos());
        mEndPos = getParent()->windowToLocal(event.getWindowPos());
    }
}

//	Touch dragged event handler
void VirtualCard::onTouchDragged(po::scene::TouchEvent &event){
    if (idInCard(event.getId())) {
        mEndPos = getParent()->windowToLocal(event.getWindowPos());
        ci::vec2 newPosition = mInitialPos + (mEndPos - mStartPos);
        setPosition(newPosition);
    }
}

//	Touch up event handler
void VirtualCard::onTouchUp(po::scene::TouchEvent &event){
    if (idInCard(event.getId())) {
        mIsPressed = false;
        removeTouchId(event.getId());
    }
}

bool VirtualCard::idInCard(uint32_t id){
    for (int i = 0; i<touchId.size(); ++i) {
        if(touchId[i] == id){
            //std::cout << id <<" is in card" << std::endl;
            return true;
        }
    }
    return false;
}

void VirtualCard::removeTouchId(uint32_t id){
    for (int i = 0; i<touchId.size(); ++i) {
        if(touchId[i] == id){
            touchId.erase(touchId.begin()+i);
            std::cout << "removing id " << id << std::endl;
        }
    }
    
}

