//
//  VirtualCard.cpp
//  MicroCosmos
//
//  Created by Johan Eriksson on 2017-04-12.
//
//

#include "VirtualCard.hpp"



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
    
    float x = Rand::randFloat(1, 700);
    float y = Rand::randFloat(1, 700);
    
    leftTX = 40.0f+x, leftTY = 40.0f+y;
    rightBX = 300.0f+x, rightBY = 300.0f+y;
    mediaRect = Rectf( leftTX, leftTY, rightBX, rightBY );
    cardOutline = Rectf( leftTX, leftTY, rightBX, rightBY );
    auto img = loadImage( loadAsset( _path ) );
    mTex = gl::Texture2d::create( img );
    
}

bool VirtualCard::isPointInShape(float x, float y) {
    bool inX = false;
    bool inY = false;
    if (x > leftTX && x < rightBX)
        inX = true;
    
    if (y > leftTY && y < rightBY)
        inY = true;
    if(inX && inY)
        std::cout << "!!!" << std::endl;
    
    return (inX && inY);
}

void VirtualCard::displayContent(){
    
    std::cout << "path: " << _path << std::endl;
    std::cout << "scale: " << _scale << std::endl;
    std::cout << "categories: ";
    
    for (unsigned long i = 0; i < _categories.size(); ++i) {
        if(i == _categories.size()-1){
            std::cout << _categories[i] << std::endl;
        }
        else{
            std::cout << _categories[i] << ", ";
        }
    }
    
    std::cout << "header_se: " << _header_se << std::endl;
    std::cout << "text_se: " << _text_se << std::endl;
    std::cout << "header_en: " << _header_en << std::endl;
    std::cout << "text_en: " << _text_en << std::endl;
}

void VirtualCard::moveCard(vec2 pPos, vec2 pos){
    float moveX = pPos[0] - pos[0];
    float moveY = pPos[1] - pos[1];
    trans[0] -= moveX;
    trans[1] -= moveY;
    leftTX -= moveX; rightBX -= moveX;
    leftTY -= moveY; rightBY -= moveY;
    cardOutline = Rectf( leftTX, leftTY, rightBX, rightBY );
    
}

bool VirtualCard::touchIdInCard(uint32_t id){
    for (int i = 0; i<touchId.size(); ++i) {
        if(touchId[i] == id){
            std::cout << id <<" is in card" << std::endl;
            return true;
        }
    }
    return false;
}


void VirtualCard::removeTouchId(uint32_t id){
    for (int i = 0; i<touchId.size(); ++i) {
        if(touchId[i] == id){
            touchId.erase(touchId.begin()+i);
            std::cout << "removing id" << std::endl;
        }
    }
    
}


void VirtualCard::draw(){
    //gl::color(0, 0, 0);
    //gl::drawStrokedRect(cardOutline);
    gl::draw(mTex, ci::Area(cardOutline.getCenteredFit(mTex->getBounds(), true)), cardOutline);
    
}
