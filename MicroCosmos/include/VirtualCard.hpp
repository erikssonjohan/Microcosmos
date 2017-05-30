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
#include "poNodeContainer.h"
#include "poShape.h"
#include "cinder/Rand.h"
#include "poTextBox.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class VirtualCard;
typedef std::shared_ptr<VirtualCard> VirtualCardRef;

class VirtualCard : public po::scene::NodeContainer {
public:

	static VirtualCardRef create(ci::Color color, std::string path, float scale, std::vector<std::string> categories, std::string header_se, std::string text_se, std::string header_en, std::string text_en);

	//sets upp det card
	void setup(ci::Color color);

	//Constructor for the card
	VirtualCard(std::string path, float scale, std::vector<std::string> categories, std::string header_se, std::string text_se, std::string header_en, std::string text_en);

	//Used for calculating forces
	float mass;
	void applyForce(ci::vec2 force);
	ci::vec2 separate(std::vector<VirtualCardRef>& v);
	float mag(float x, float y);
	ci::vec2 limit(ci::vec2 v, float max);
	void setRcPos(ci::vec2 rcp);
	void update();

private:

	//Used for calculating forces
	double time3_;
	ci::vec2 velocity_;
	ci::vec2 acceleration_;
	ci::vec2 real_card_pos_;
	float top_speed_;
	float max_force_;

    //media
    float media_width_, media_height_;
    bool media_movie_;
    
	float border_ = 10;
	//timestamps that handle how long an event has been pressed
	double start_, end_, time_touched_, time1_, time2_;
	bool time_checker_ = true;
	bool check_ = true;
	bool doubleCheck = false;


	po::scene::ShapeRef mBase_shape_;
	ci::vec2            mBase_position_;
	ci::Color           mBase_color_;

	//touch vector
    std::vector<uint32_t> touch_id_;
	std::vector<po::scene::TouchEvent> events_;
	std::vector<vec2> pPos_;

	po::scene::ShapeRef textFig_;
	po::scene::TextBoxRef text_contentS_;
	po::scene::TextBoxRef text_contentE_;
	po::scene::TextBoxRef text_headerS_;
	po::scene::TextBoxRef text_headerE_;
	po::scene::ShapeRef button_texture_;
	ci::gl::TextureRef button_imgS_;
	ci::gl::TextureRef button_imgE_;
	ci::vec2 button_scale_;
	bool text_visible_ = false;
	bool text_SWE_ = true;

	float angle_ = 0.0f;
	std::string path_;
	float scale_;
	std::vector<std::string> categories_;
	std::string header_se_;
	std::string text_se_;
	std::string header_en_;
	std::string text_en_;

	//	Keep tracking_ of the initial, start and end position to use for dragging
	ci::vec2 mStartPos_, mEndPos_, mInitialPos_;

	//removes touch id from card
	void removeTouchId(uint32_t id);

	// Checks if card has the touch id
	bool idInCard(uint32_t id);

	//Checks if touch is in button
	bool touchInButton(po::scene::TouchEvent event);

	//removes touch id from card
	void removeTouchEvent(po::scene::TouchEvent tEvent);

	//	Keep tracking_ on pressed for dragging
	bool mIsPressed;

	void onTouchDown(po::scene::TouchEvent &event);
	
	void onTouchDragged(po::scene::TouchEvent &event);

	//	Touch up event handler
	void onTouchUp(po::scene::TouchEvent &event);

	//Scale
	void scale(ci::vec2 pos1, ci::vec2 pPos1, ci::vec2 pos2, ci::vec2 pPos2);
    
    void touchRotate(ci::vec2 pos1, ci::vec2 pPos1, ci::vec2 pos2, ci::vec2 pPos2);

	//Function that creates the text box with swedish and english content
	void createTextBox();

	//Function that handles the visibility of all the text boxes and buttons.
	void handleButtonTouches(po::scene::TouchEvent event);

	// Function that checks if a double touch were occured
	bool doubleTouch(po::scene::TouchEvent event);
};
#endif /* VirtualCard_hpp */
