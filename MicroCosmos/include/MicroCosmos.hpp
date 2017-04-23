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

class MicroCosmos;
typedef std::shared_ptr<MicroCosmos> MicroCosmosRef;

class MicroCosmos
: public po::scene::NodeContainer
{
public:
    static MicroCosmosRef create();
    
    void setup();
    void loadXML(const char *file, std::vector<VirtualCardRef> &cards);
    
    
protected:
    
private:
    std::vector<VirtualCardRef> cards;
    
    
};





#endif /* MicroCosmos_hpp */
