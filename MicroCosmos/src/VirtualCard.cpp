//
//  VirtualCard.cpp
//  MicroCosmos
//
//  Created by Oscar Nord on 2017-04-21.
//
//

#include "VirtualCard.hpp"

#include "poVideo.h"
#include "poShape.h"

#include "cinder/qtime/QuickTimeGl.h"
#include "cinder/ImageIo.h"
#include "cinder/Utilities.h"

using namespace po::scene;



VirtualCard::VirtualCard(std::string path, float scale, std::vector<std::string> categories, std::string header_se,
	std::string text_se, std::string header_en, std::string text_en)
{
	_path = path;
	_scale = scale;
	_categories = categories;
	_header_se = header_se;
	_text_se = text_se;
	_header_en = header_en;
	_text_en = text_en;


	cinder::gl::TextureRef mFrameTexture;
	cinder::gl::TextureRef texture;

	x = ci::Rand::randFloat(1, 800);
	y = ci::Rand::randFloat(1, 800);


}

VirtualCardRef VirtualCard::create(ci::Color color, std::string path, float scale, std::vector<std::string> categories, std::string header_se,
	std::string text_se, std::string header_en, std::string text_en)
{
	VirtualCardRef ref(new VirtualCard(path, scale, categories, header_se,
		text_se, header_en, text_en));
	ref->setup(color);
	return ref;
}




void VirtualCard::setup(ci::Color color)
{
	mStartPos = ci::vec2();
	mEndPos = ci::vec2();
	mInitialPos = ci::vec2();
	mIsPressed = false;
    po::scene::ShapeRef textur;
    po::scene::VideoGlRef poVideo;
    
    if(_path.substr(_path.find_last_of(".")+1) == "mov" || _path.substr(_path.find_last_of(".")+1) == "mp4"){
        
        mediaMovie = true;
        
        poVideo = po::scene::VideoGl::create();
        
        try {
            ci::qtime::MovieGlRef movieRef = ci::qtime::MovieGl::create(ci::app::getAssetPath(_path));
            
            poVideo->setMovieRef(movieRef);
            poVideo->getMovieRef()->setLoop(true);
            poVideo->getMovieRef()->play();
        } catch (...) {
            ci::app::console() << "PlayerNode::setup: Failed to load movie" << std::endl;
        }
        
        poVideo->setPosition(border, border);
        mediaWidth = poVideo->getWidth();
        mediaHeight = poVideo->getHeight();
    }
    else if(_path.substr(_path.find_last_of(".")+1) == "jpg" || _path.substr(_path.find_last_of(".")+1) == "png" ){
        mediaMovie = false;
        ci::gl::TextureRef img = ci::gl::Texture::create(ci::loadImage(ci::app::loadAsset(_path)));
        //ci::gl::TextureRef buttonImg = ci::gl::Texture::create(ci::loadImage(ci::app::loadAsset("sweeng.png")));
        mediaWidth = img->getWidth();
        mediaHeight = img->getHeight();
        //  create and add the shape to the node container
        textur = Shape::createRect(img->getWidth(), img->getHeight());
        textur->setTexture(img);
        textur->setPosition(border, border);
    }
    
    
    //border to the media (img or movie)
    mBaseShape = Shape::createRect(mediaWidth + border * 2, mediaHeight + border * 2);
    mBaseColor = color;
    mBaseShape->setFillColor(color);

    
    
	// text
	// TODO:: make it less static and might need some fixes. just did it to test, not sure if its the best way // JE
	textFig = Shape::createRect(400, mediaHeight + border * 2);
	textFig->setFillColor(0, 0, 0, 0.8);
	textFig->setPosition(mediaWidth + border * 2, 0);
	buttonWidth = mediaWidth / 8;
	buttonHeight = mediaHeight / 10;
	buttonFig = Shape::createRect(buttonWidth, buttonHeight);
	buttonFig->setFillColor(0, 0, 0, 0.3);
	buttonPos = ci::vec2(mediaWidth + border * 2, mediaHeight + border * 2 - buttonHeight);
	buttonFig->setPosition(buttonPos.x, buttonPos.y);

	//Textbox
	ci::TextBox ciTextBox = ci::TextBox();
	//auto textB = po::scene::TextBox::create(ciTextBox);
	ciTextBox.size(300, 500);
	ciTextBox.color(ci::Color(1, 1, 1));
	ciTextBox.alignment(ci::TextBox::Alignment::LEFT);
	ciTextBox.font(ci::Font("Arial", 20));
	//Button box
	ci::TextBox ciButtonBox = ci::TextBox();
	ciButtonBox.size(buttonWidth, buttonHeight);
	ciButtonBox.color(ci::Color(1, 1, 1));
	ciButtonBox.alignment(ci::TextBox::Alignment::CENTER);
	ciButtonBox.font(ci::Font("Arial", 25));

	ciTextBox.text(_text_se);
	textContentS = po::scene::TextBox::create(ciTextBox);
	textContentS->setPosition(mediaWidth + border * 6, 100);
	ciTextBox.text(_text_en);
	textContentE = po::scene::TextBox::create(ciTextBox);
	textContentE->setPosition(mediaWidth + border * 6, 100);
	ciButtonBox.text("SWE/ENG");
	SWE = po::scene::TextBox::create(ciButtonBox);
	SWE->setPosition(buttonPos.x, buttonPos.y);
	ciButtonBox.text("ENG/SWE");
	ENG = po::scene::TextBox::create(ciButtonBox);
	ENG->setPosition(buttonPos.x, buttonPos.y);

	//Just so it dosent take all of the screen...
	setScale(_scale);

	setAlignment(po::scene::Alignment::CENTER_CENTER);

	addChild(mBaseShape);
    
    if (!mediaMovie){
	addChild(textur);
    }
    if (mediaMovie){
        addChild(poVideo);
    }
	addChild(textFig);
	addChild(textContentS);
	addChild(textContentE);
	setName(_header_se);
	addChild(buttonFig);
	addChild(SWE);
	addChild(ENG);

	textFig->setVisible(false);
	textContentS->setVisible(false);
	textContentE->setVisible(false);
	buttonFig->setVisible(false);
	SWE->setVisible(false);
	ENG->setVisible(false);


	getSignal(po::scene::TouchEvent::BEGAN_INSIDE).connect(std::bind(&VirtualCard::onTouchDown, this, std::placeholders::_1));
	getSignal(po::scene::TouchEvent::MOVED_INSIDE).connect(std::bind(&VirtualCard::onTouchDragged, this, std::placeholders::_1));
	getSignal(po::scene::TouchEvent::MOVED).connect(std::bind(&VirtualCard::onTouchDragged, this, std::placeholders::_1));
	getSignal(po::scene::TouchEvent::ENDED_INSIDE).connect(std::bind(&VirtualCard::onTouchUp, this, std::placeholders::_1));
	getSignal(po::scene::TouchEvent::ENDED).connect(std::bind(&VirtualCard::onTouchUp, this, std::placeholders::_1));
	//buttonFig->getSignal(po::scene::TouchEvent::Type::ENDED_INSIDE).connect(std::bind(&VirtualCard::onButtonUp, this, std::placeholders::_1));

}

void VirtualCard::onTouchDown(po::scene::TouchEvent &event) {
	start = ci::app::getElapsedSeconds();
	/*
	if(doubleTouch(event)) {
		//mBaseShape->setVisible(false);
		//.... What should the doubletouch do??
		
	}
	*/
	if (!idInCard(event.getId())) {
		std::cout << "tryck " << event.getId() << std::endl;
		mIsPressed = true;
		touchId.push_back(event.getId());
		events.push_back(event);

		pPos.push_back(event.getScenePos());

		// Moves the card to drawn at the front
		getParent()->moveChildToFront(getParent()->getChildByName(this->getName()));

		if (touchId.size() == 1) {
			// Update the position of the card
			mInitialPos = getPosition();
			mStartPos = getParent()->windowToLocal(event.getWindowPos());
			mEndPos = getParent()->windowToLocal(event.getWindowPos());
		}
	}
}


//	Touch dragged event handler
void VirtualCard::onTouchDragged(po::scene::TouchEvent &event) {
	if (idInCard(event.getId()) && touchId[0] == event.getId()) {
		mEndPos = getParent()->windowToLocal(event.getWindowPos());
		ci::vec2 newPosition = (mInitialPos + (mEndPos - mStartPos));
		//newPosition.x *=0.5;
		//newPosition.y *=0.5;
		setPosition(newPosition);

	}
	if (events.size() >= 2) {
		scale(events[0].getScenePos(), pPos[0], events[1].getScenePos(), pPos[1]);
		setScale(_scale);
        touchRotate(events[0].getScenePos(), pPos[0], events[1].getScenePos(), pPos[1]);
        setRotation( angle);
	}
	for (int i = 0; i<events.size(); ++i) {
		if (events[i].getId() == event.getId()) {
			pPos[i] = events[i].getScenePos();
			events[i] = event;
		}
	}



}

//	Touch up event handler
void VirtualCard::onTouchUp(po::scene::TouchEvent &event) {
	if (idInCard(event.getId()))
	{
		end = ci::app::getElapsedSeconds();
		double timeTouched = (end - start);
		//console() << "Time card was touched " << timeTouched << std::endl;
		if (timeTouched < 0.350) {
			handleButtonTouches(event);
		}

		mIsPressed = false;
		removeTouchId(event.getId());
		removeTouchEvent(event);
	}
}

bool VirtualCard::idInCard(uint32_t id) {
	for (int i = 0; i<touchId.size(); ++i) {
		if (touchId[i] == id) {
			//std::cout << id <<" is in card" << std::endl;
			return true;
		}
	}
	return false;
}
bool VirtualCard::touchInButton(po::scene::TouchEvent event) {
	if (event.getLocalPos().x >= buttonPos.x && event.getLocalPos().x <= (buttonPos.x + buttonWidth) && event.getLocalPos().y >= buttonPos.y && event.getLocalPos().y <= buttonPos.y + buttonHeight) {
		return true;
	}
	return false;
}

void VirtualCard::removeTouchId(uint32_t id) {
	for (int i = 0; i<touchId.size(); ++i) {
		if (touchId[i] == id) {
			touchId.erase(touchId.begin() + i);
			std::cout << "removing id " << id << std::endl;
		}
	}

}

//removes touch id from card
void VirtualCard::removeTouchEvent(po::scene::TouchEvent tEvent) {
	for (int i = 0; i<events.size(); ++i) {
		if (events[i].getId() == tEvent.getId()) {
			events.erase(events.begin() + i);
			pPos.erase(pPos.begin() + i);
		}
	}
}

void VirtualCard::scale(ci::vec2 pos1, ci::vec2 pPos1, ci::vec2 pos2, ci::vec2 pPos2) {

	float currentDistance = sqrt(pow(pos1[0] - pos2[0], 2) + pow(pos1[1] - pos2[1], 2));
	float previousDistance = sqrt(pow(pPos1[0] - pPos2[0], 2) + pow(pPos1[1] - pPos2[1], 2));

	// Guard against division by zero & nan
	if (previousDistance != 0 && previousDistance == previousDistance) {
		_scale *= currentDistance / previousDistance;
		//setScale(_scale);
	}
}

void VirtualCard::touchRotate(ci::vec2 pos1, ci::vec2 pPos1, ci::vec2 pos2, ci::vec2 pPos2) {
    vec2 a = pos1-pos2;
    vec2 b = pPos1-pPos2;
    a = normalize(a);
    b = normalize(b);

    angle += atan2(b.y, b.x)-atan2(a.y, a.x);
    std::cout << angle << std::endl;
}

void VirtualCard::handleButtonTouches(po::scene::TouchEvent event) {
	if (touchInButton(event) && textVisible)
	{
		//console() << "X = " << event.getLocalPos().x << ", Y =" << event.getLocalPos().y << std::endl;
		if (textSWE)
		{
			textContentE->setVisible(true);
			textContentS->setVisible(false);
			ENG->setVisible(true);
			SWE->setVisible(false);

			textSWE = false;
		}
		else
		{
			textContentS->setVisible(true);
			textContentE->setVisible(false);
			SWE->setVisible(true);
			ENG->setVisible(false);

			textSWE = true;
		}
	}
	else if (textVisible)
	{
		textFig->setVisible(false);
		textContentS->setVisible(false);
		textContentE->setVisible(false);
		buttonFig->setVisible(false);
		SWE->setVisible(false);
		ENG->setVisible(false);
		textVisible = false;
	}
	else
	{
		textFig->setVisible(true);
		textContentS->setVisible(true);
		buttonFig->setVisible(true);
		SWE->setVisible(true);
		textVisible = true;
	}
}



bool VirtualCard::doubleTouch(po::scene::TouchEvent event) {

	
	if (timeChecker) {
		time1 = getElapsedSeconds();
		
	}
	else if (timeChecker != true) {
		time2 = getElapsedSeconds();
		

	}
	if (time2 - time1 < 0.5 && timeChecker != true) {
		timeChecker = true;
		return true;

	}


	else
		if (timeChecker) {
			timeChecker = false;
			
		}
		else
			timeChecker = true;
		
	return false;

		

}

