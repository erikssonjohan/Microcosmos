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
    mIsPressed = false;

    ci::gl::TextureRef img =  ci::gl::Texture::create(ci::loadImage(ci::app::loadAsset(_path) ));

    //  create and add the shape to the node container
    mBaseShape = Shape::createRect(img->getWidth()+border*2, img->getHeight()+border*2);
    mBaseColor = color;
    mBaseShape->setFillColor(color);
    auto textur = Shape::createRect(img->getWidth(), img->getHeight());
    textur->setTexture(img);
    textur->setPosition(border, border);


    // text
    // TODO:: make it less static and might need some fixes. just did it to test, not sure if its the best way // JE
    textFig = Shape::createRect(400, img->getHeight()+border*2);
    textFig->setFillColor(0,0,0,0.8);
    textFig->setPosition(img->getWidth()+border*2, 0);
    ci::TextBox ciTextBox = ci::TextBox();
    //auto textB = po::scene::TextBox::create(ciTextBox);
    ciTextBox.size(300, 500);
    ciTextBox.color(ci::Color(1, 1, 1));
    ciTextBox.text(_text_se);
    ciTextBox.alignment(ci::TextBox::Alignment::LEFT);
    ciTextBox.font(ci::Font("Arial", 20));
    textContent = po::scene::TextBox::create(ciTextBox);
    textContent->setPosition(img->getWidth()+border*6, 100);


    //Just so it dosent take all of the screen...
    setScale(0.6, 0.6);

    addChild(mBaseShape);
    addChild(textur);
    addChild(textFig);
    addChild(textContent);
    setName(_header_se);

    textFig->setVisible(false);
    textContent->setVisible(false);
    
    
    getSignal(po::scene::TouchEvent::BEGAN_INSIDE).connect(std::bind(&VirtualCard::onTouchDown, this, std::placeholders::_1));
    getSignal(po::scene::TouchEvent::MOVED_INSIDE).connect(std::bind(&VirtualCard::onTouchDragged, this, std::placeholders::_1));
    getSignal(po::scene::TouchEvent::MOVED).connect(std::bind(&VirtualCard::onTouchDragged, this, std::placeholders::_1));
    getSignal(po::scene::TouchEvent::ENDED_INSIDE).connect(std::bind(&VirtualCard::onTouchUp, this, std::placeholders::_1));
    getSignal(po::scene::TouchEvent::ENDED).connect(std::bind(&VirtualCard::onTouchUp, this, std::placeholders::_1));

    
}

void VirtualCard::onTouchDown(po::scene::TouchEvent &event){
    if (!idInCard(event.getId())) {
        std::cout << "tryck " << event.getId() << std::endl;
        mIsPressed = true;
        touchId.push_back(event.getId());
        events.push_back(event);

        textFig->setVisible(true);
        textContent->setVisible(true);


        // Moves the card to drawn at the front
        getParent()->moveChildToFront(getParent()->getChildByName(this->getName()));

        if(touchId.size() == 1) {
            // Update the position of the card
            mInitialPos = getPosition();
            mStartPos = getParent()->windowToLocal(event.getWindowPos());
            mEndPos = getParent()->windowToLocal(event.getWindowPos());
        }

        if(events.size() == 2) {
            std::cout << events[0].getLocalPos() ;
        }

    }
}

//	Touch dragged event handler
void VirtualCard::onTouchDragged(po::scene::TouchEvent &event){
    if (idInCard(event.getId()) && touchId[0] == event.getId()) {
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
        removeTouchEvent(event);
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

//removes touch id from card
void VirtualCard::removeTouchEvent(po::scene::TouchEvent tEvent){
    for (int i = 0; i<events.size(); ++i) {
        if(events[i].getId() == tEvent.getId()){
            events.erase(events.begin()+i);
        }
    }
}

