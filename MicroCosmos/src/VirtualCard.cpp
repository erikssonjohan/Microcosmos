//
//  VirtualCard.cpp
//  MicroCosmos
//
//  Created by Oscar Nord on 2017-04-21.
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
    
    float x = Rand::randFloat(1, 800);
    float y = Rand::randFloat(1, 800);
    
    leftTX = 0.0f, leftTY = 0.0f;
    rightBX = 300.0f, rightBY = 300.0f;
    mediaRect = Rectf( leftTX, leftTY, rightBX, rightBY );
    cardOutline = Rectf( leftTX, leftTY, rightBX, rightBY );
    auto img = loadImage( loadAsset( _path ) );
    mTex = gl::Texture2d::create( img );
    trans[0] += x;
    trans[1] += y;
    
    
}

bool VirtualCard::isPointInShape(float x, float y) {
    bool inX = false;
    bool inY = false;
    if (x > leftTX+trans[0] && x < rightBX+trans[0])
        inX = true;
    
    if (y > leftTY+trans[1] && y < rightBY+trans[1])
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
    //leftTX -= moveX; rightBX -= moveX;
    //leftTY -= moveY; rightBY -= moveY;
    //cardOutline = Rectf( leftTX, leftTY, rightBX, rightBY );
}

void VirtualCard::scaleCard(vec2 fingerPos1, vec2 fingerPos2){
    float scale = 1;
}

bool VirtualCard::touchIdInCard(uint32_t id){
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
            std::cout << "removing id" << std::endl;
        }
    }
    
}


void VirtualCard::draw(){
    //gl::color(0, 0, 0);
    //gl::drawStrokedRect(cardOutline);
    gl::draw(mTex, ci::Area(cardOutline.getCenteredFit(mTex->getBounds(), true)), cardOutline);
    
}

