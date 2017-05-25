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
#include "Tracking.hpp"
class MicroCosmos;
typedef std::shared_ptr<MicroCosmos> MicroCosmosRef;

class MicroCosmos : public po::scene::NodeContainer {
public:
    static MicroCosmosRef create();
    
    void setup();
    void uniqueCategories(const char *file, std::vector<std::string> &categories);
    bool stringInVector(std::string category, std::vector<std::string> categories);
	void update();
	void setIdCoordinates();
    
private:
    std::vector<RealCardRef> realcards_;

	std::vector<uint32_t> touchid_;
	std::vector<po::scene::TouchEvent> events_;
	std::map<int,string> id_categories_;
	std::map<glm::vec2, string> categories_coordinates_;
    void onTouchDown(po::scene::TouchEvent &event);
    
    //	Touch up event handler
    void onTouchUp(po::scene::TouchEvent &event);

	void removeTouchId(uint32_t id);

	void removeTouchEvent(po::scene::TouchEvent tEvent);

	bool found_realcard_ = false;
	Tracking tracking_;
	glm::vec3 pos_;
	glm::vec2 realpos_;
	int calculateframe_ = 10;
    
    void loadXML(const char *file, std::vector<std::vector<VirtualCardRef>> &cards, std::vector<std::string> category);
};





#endif /* MicroCosmos_hpp */
