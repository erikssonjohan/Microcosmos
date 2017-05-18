#pragma once

#include <stdio.h>
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "poNodeContainer.h"
#include "poShape.h"
#include "cinder/Rand.h"
#include "VirtualCard.hpp"
#include "cinder/Xml.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class RealCard;
typedef std::shared_ptr<RealCard> RealCardRef;

class RealCard
: public po::scene::NodeContainer
{
public:
    
    static RealCardRef create(std::string category,std::vector<VirtualCardRef> cards);
    void setup(std::string category, std::vector<VirtualCardRef> cards);
	
	string get_Category();
    
    bool findTouchpoints(); //return true if card touchpoints were found and linked to RealCard

private:
    
    std::vector<VirtualCardRef> vCards;
	int ID;
	po::scene::ShapeRef circle;

	string Category;
    
    std::vector<uint32_t> touchId; //vector of card legs touchId, first is sharp edge
    std::vector<po::scene::TouchEvent> events;
    
    



    void setV(bool v);

};