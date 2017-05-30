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
#include "poShape.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class RealCard;
typedef std::shared_ptr<RealCard> RealCardRef;

class RealCard : public po::scene::NodeContainer {
public:
    static RealCardRef create(std::string category,int id, std::vector<VirtualCardRef> cards);
    void setup(std::string category,int id, std::vector<VirtualCardRef> cards);
	
    std::string getCategory();
    void setV(bool v);
	int getId();

	bool findTouchpoints(); //return true if card touchpoints were found and linked to RealCard

	//Used in calculation of forces
	void update();
	float constrain(float val, float min, float max);

	//Initiate the position of the virtualcards_ around the realcard
	void initVcards(glm::vec2 rCardPos);
	//Sets the initiated bool to false when realcard is lifted of the table
	void resetInitiation();
	bool legsFound() {
		return (touchid_.size() == 3);
	};

	void clearLegEvents();
private:
    std::vector<VirtualCardRef> virtualcards_;
	int id_ = 0;
	po::scene::ShapeRef circle_;

	std::string category_;
    
    std::vector<uint32_t> touchid_; //vector of card legs touchid, first is sharp edge
    std::vector<po::scene::TouchEvent> events_;
	std::vector<po::scene::TouchEvent> leg_events_;

	//False until a realCard has been detected on the screen by tracking
	bool realcard_initiated_ = false;

	void onTouchDown(po::scene::TouchEvent &event);
	void onTouchDragged(po::scene::TouchEvent &event);
	void onTouchUp(po::scene::TouchEvent &event);
	void removeTouchEvent(po::scene::TouchEvent tEvent);
	

	//Forces
	ci::vec2 attract(VirtualCardRef& c);
	float g_ = 1;
	float mass_ = 100;
};
