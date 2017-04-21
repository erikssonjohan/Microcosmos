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
#include "cinder/Rand.h"
using namespace ci;
using namespace ci::app;
using namespace std;


class VirtualCard {
public:
    /*!
     *
     * A constructor for the VirtualCard just based on the XML
     *
     * @param path - path to the media (image/film)
     * @param scale - scaling of the media
     * @param categories - the contents categories
     * @param header_se - the header/name of the content (se)
     * @param text_se - the text of the content (se)
     * @param header_en he header/name of the content (en)
     * @param text_en - the text of the content (en)
     */
    VirtualCard(std::string path, float scale, std::vector<std::string> categories, std::string header_se,
                std::string text_se, std::string header_en, std::string text_en );
    
    /*!
     * Prints the @p path, @p scale, @p categories, @p header_se, @p text_se, @p header_en and @p text_en in the console
     */
    void displayContent();
    
    void draw();
    
    bool isPointInShape(float x, float y);
    
    void moveCard(vec2 pPos, vec2 pos);
    void scaleCard(vec2 fingerPos1, vec2 fingerPos2);
    
    bool touchIdInCard(uint32_t id);
    void removeTouchId(uint32_t id);
    
    Rectf mediaRect;
    Rectf cardOutline;
    float leftTX , leftTY;
    float rightBX , rightBY;
    
    std::vector<uint32_t> touchId;
    void setPos(vec2 pos);
    vec2 trans = {0, 0};
    float radAngle = 0.0f;
    
private:
    
    std::string _path;
    float _scale;
    std::vector<std::string> _categories;
    std::string _header_se;
    std::string _text_se;
    std::string _header_en;
    std::string _text_en;
    gl::Texture2dRef mTex;
    
};




#endif /* VirtualCard_hpp */

