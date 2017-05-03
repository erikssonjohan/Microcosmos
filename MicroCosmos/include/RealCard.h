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
    
    static RealCardRef create(std::string category,int id);
    void setup(std::string category,int id);
    void loadXML(const char *file, std::vector<VirtualCardRef> &cards, std::string category);
	int get_ID();
private:
    
    std::vector<VirtualCardRef> vCards;
	int ID;
    
    
    
};