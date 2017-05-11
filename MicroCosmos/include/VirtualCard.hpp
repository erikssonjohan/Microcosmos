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

class VirtualCard
	: public po::scene::NodeContainer
{
public:

	static VirtualCardRef create(ci::Color color, std::string path, float scale, std::vector<std::string> categories, std::string header_se, std::string text_se, std::string header_en, std::string text_en);

	//sets upp det card
	void setup(ci::Color color);

	//Constructor for the card
	VirtualCard(std::string path, float scale, std::vector<std::string> categories, std::string header_se, std::string text_se, std::string header_en, std::string text_en);

	float x, y;

protected:

private:

    
    //media
    float mediaWidth, mediaHeight;
    bool mediaMovie;
    
	float border = 10;
	//timestamps that handle how long an event has been pressed
	double start, end, timeTouched, time1, time2;
	bool timeChecker = true;
	bool check = true;


	po::scene::ShapeRef mBaseShape;
	ci::vec2            mBasePosition;
	ci::Color           mBaseColor;

	//touch vector
	std::vector<uint32_t> touchId;
	std::vector<po::scene::TouchEvent> events;
	std::vector<vec2> pPos;

	po::scene::ShapeRef textFig;
	po::scene::TextBoxRef textContentS;
	po::scene::TextBoxRef textContentE;
	po::scene::TextBoxRef textHeaderS;
	po::scene::TextBoxRef textHeaderE;
	po::scene::ShapeRef buttonTextur;
	ci::gl::TextureRef buttonImgS;
	ci::gl::TextureRef buttonImgE;
	ci::vec2 buttonScale;
	bool textVisible = false;
	bool textSWE = true;

	float angle = 0.0f;
	std::string _path;
	float _scale = 0.2;
	std::vector<std::string> _categories;
	std::string _header_se;
	std::string _text_se;
	std::string _header_en;
	std::string _text_en;

	//	Keep track of the initial, start and end position to use for dragging
	ci::vec2 mStartPos, mEndPos, mInitialPos;

	//removes touch id from card
	void removeTouchId(uint32_t id);

	// Checks if card has the touch id
	bool idInCard(uint32_t id);

	//Checks if touch is in button
	bool touchInButton(po::scene::TouchEvent event);

	//removes touch id from card
	void removeTouchEvent(po::scene::TouchEvent tEvent);

	//	Keep track on pressed for dragging
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



	//MARTIN ANVÄNDER DETTA NEDANFÖR FÖR ATT TESTA TEXTRUTAN DÅ HANS EMULERING EJ LÄNGRE FUNGERAR
	/*
	void onMouseDown(po::scene::MouseEvent &event);
	//	Touch dragged event handler
	//Checks if mouse is in button
	bool mouseInButton(po::scene::MouseEvent event);
	void handleButtonClicks(po::scene::MouseEvent event);
	*/
	//HÄR TAR MARTINS SKIT SLUT
};




#endif /* VirtualCard_hpp */

