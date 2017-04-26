//
//  MicroCosmos.hpp
//  MicroCosmos
//
//  Created by Johan Eriksson on 2017-04-22.
//
//

#pragma once
#ifndef MicroCosmos_hpp
#define MicroCosmos_hpp

#include <stdio.h>
#include "poNodeContainer.h"
#include "VirtualCard.hpp"
#include "cinder/Xml.h"
#include "RealCard.h"

class MicroCosmos;
typedef std::shared_ptr<MicroCosmos> MicroCosmosRef;

class MicroCosmos
: public po::scene::NodeContainer
{
public:
    static MicroCosmosRef create();
    
    void setup();
    
    void uniqueCategories(const char *file, std::vector<std::string> &categories);
    bool stringInVector(std::string category, std::vector<std::string> categories);
    
protected:
    
private:
    
    //std::vector<VirtualCardRef> cards;
    std::vector<RealCardRef> rcards;
    
    void onTouchDown(po::scene::TouchEvent &event);
    
    //	Touch up event handler
    void onTouchUp(po::scene::TouchEvent &event);
    
    
};





#endif /* MicroCosmos_hpp */
