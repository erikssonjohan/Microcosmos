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

class RealCard : public po::scene::NodeContainer {
public:
    static RealCardRef create(std::string category,int id, std::vector<VirtualCardRef> cards);
    void setup(std::string category,int id, std::vector<VirtualCardRef> cards);
	
	string get_Category();
    void setV(bool v);
	int get_ID();

	bool findTouchpoints(); //return true if card touchpoints were found and linked to RealCard

	//Used in calculation of forces
	void update();
	float constrain(float val, float min, float max);

	//Initiate the position of the vCards around the realcard
	void initVcards(glm::vec2 rCardPos);
	//Sets the initiated bool to false when realcard is lifted of the table
	void resetInitiation();

private:
    std::vector<VirtualCardRef> vCards;
	int ID=0;
	po::scene::ShapeRef circle;

	string Category;
    
    std::vector<uint32_t> touchId; //vector of card legs touchId, first is sharp edge
    std::vector<po::scene::TouchEvent> events;

	//False until a realCard has been detected on the screen by tracking
	bool rCardInitiated = false;

	//Forces
	ci::vec2 attract(VirtualCardRef& c);
	float G;
	float mass;
};
