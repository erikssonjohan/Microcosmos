//
//  VirtualCard.cpp
//  MicroCosmos
//
//  Created by Oscar Nord on 2017-04-21.
//
//

#include "VirtualCard.hpp"

//#include "poVideo.h" // VIDEO !!!
#include "poShape.h"

// #include "cinder/qtime/QuickTimeGl.h" // VIDEO !!!
#include "cinder/ImageIo.h"
#include "cinder/Utilities.h"

using namespace po::scene;



VirtualCard::VirtualCard(std::string path, float scale, std::vector<std::string> categories, std::string header_se,
	std::string text_se, std::string header_en, std::string text_en)
{
	path_ = path;
	scale_ = scale;
	categories_ = categories;
	header_se_ = header_se;
	text_se_ = text_se;
	header_en_ = header_en;
	text_en_ = text_en;


	cinder::gl::TextureRef mFrameTexture;
	cinder::gl::TextureRef texture;

	x = ci::Rand::randFloat(1, 800);
	y = ci::Rand::randFloat(1, 800);
	//x = 400.0f;
	//y = 400.0f;

	//Forces
	velocity_ = ci::vec2(0, 0);
	acceleration_ = ci::vec2(0, 0);
	top_speed_ = (float)10;
	max_force_ = (float)0.3;
	mass = (float)20;

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
	mStartPos_ = ci::vec2();
	mEndPos_ = ci::vec2();
	mInitialPos_ = ci::vec2();
	mIsPressed = false;
    po::scene::ShapeRef textur;
    setName(header_se_);
	
    //po::scene::VideoGlRef poVideo; // VIDEO !!!
    
    // VIDEO !!!
    /*if(_path.substr(_path.find_last_of(".")+1) == "mov" || _path.substr(_path.find_last_of(".")+1) == "mp4"){
        
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
    else*/ if(path_.substr(path_.find_last_of(".")+1) == "jpg" || path_.substr(path_.find_last_of(".")+1) == "png" ){
        media_movie_ = false;
        ci::gl::TextureRef img = ci::gl::Texture::create(ci::loadImage(ci::app::loadAsset(path_)));
        media_width_ = img->getWidth();
        media_height_ = img->getHeight();
        //  create and add the shape to the node container
        textur = Shape::createRect(img->getWidth(), img->getHeight());
        textur->setTexture(img);
        textur->setPosition(border_, border_);

    }
    
    
    //border to the media (img or movie)
    mBase_shape_ = Shape::createRect(media_width_ + border_ * 2, media_height_ + border_ * 2);
    mBase_color_ = color;
    mBase_shape_->setFillColor(color);

  
	// Create the text box and all content relevant to it.
	createTextBox();

	setAlignment(po::scene::Alignment::CENTER_CENTER);

	addChild(mBase_shape_);
    
    if (!media_movie_){
	addChild(textur);
    }
	
    /*if (mediaMovie){ // VIDEO !!!
        addChild(poVideo);
    }*/
	addChild(textFig_);
	addChild(text_contentS_);
	addChild(text_contentE_);
	addChild(text_headerS_);
	addChild(text_headerE_);
	addChild(button_texture_);

	button_texture_->setVisible(false);
	textFig_->setVisible(false);
	text_contentS_->setVisible(false);
	text_contentE_->setVisible(false);
	text_headerS_->setVisible(false);
	text_headerE_->setVisible(false);
    
    //Just so it dosent take all of the screen...
    setScale(_scale);

	getSignal(po::scene::TouchEvent::BEGAN_INSIDE).connect(std::bind(&VirtualCard::onTouchDown, this, std::placeholders::_1));
	getSignal(po::scene::TouchEvent::MOVED_INSIDE).connect(std::bind(&VirtualCard::onTouchDragged, this, std::placeholders::_1));
	getSignal(po::scene::TouchEvent::MOVED).connect(std::bind(&VirtualCard::onTouchDragged, this, std::placeholders::_1));
	getSignal(po::scene::TouchEvent::ENDED_INSIDE).connect(std::bind(&VirtualCard::onTouchUp, this, std::placeholders::_1));
	getSignal(po::scene::TouchEvent::ENDED).connect(std::bind(&VirtualCard::onTouchUp, this, std::placeholders::_1));
	//MARTIN ANV�NDER DENNA F�R O TESTA//getSignal(po::scene::MouseEvent::DOWN_INSIDE).connect(std::bind(&VirtualCard::onMouseDown, this, std::placeholders::_1));
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

		pPos.push_back(event.getWindowPos());

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
        //ci::vec2 newPosition = (mInitialPos + (mEndPos - mStartPos));
        ci::vec2 newPosition = getPosition();
         newPosition.x += events[0].getWindowPos().x-pPos[0].x;
        newPosition.y += events[0].getWindowPos().y-pPos[0].y;
		setPosition(newPosition);

	}
	if (events.size() >= 2) {
		scale(events[0].getWindowPos(), pPos[0], events[1].getWindowPos(), pPos[1]);
		setScale(_scale);
        touchRotate(events[0].getWindowPos(), pPos[0], events[1].getWindowPos(), pPos[1]);
        setRotation( angle);
	}
	for (int i = 0; i<events.size(); ++i) {
		if (events[i].getId() == event.getId()) {
			pPos[i] = events[i].getWindowPos();
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
	if (event.getLocalPos().x >= buttonTextur->getPosition().x && event.getLocalPos().x <= (buttonTextur->getPosition().x + buttonTextur->getScaledWidth()) && event.getLocalPos().y >= buttonTextur->getPosition().y && event.getLocalPos().y <= buttonTextur->getPosition().y + buttonTextur->getScaledHeight()) {
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
        
        //Set boundaries of scale.
        if(_scale > 0.8){
            _scale = 0.8;
        }
        if(_scale < 0.5){
            _scale = 0.5;
        }
	}
}

void VirtualCard::touchRotate(ci::vec2 pos1, ci::vec2 pPos1, ci::vec2 pos2, ci::vec2 pPos2) {
    vec2 a = pos2-pos1;
    vec2 b = pPos2-pPos1;
    a = normalize(a);
    b = normalize(b);

    angle += atan2(a.y, a.x)-atan2(b.y, b.x);
    std::cout << angle << std::endl;
}

void VirtualCard::createTextBox() {
	// TODO:: make it less static and might need some fixes. just did it to test, not sure if its the best way // JEx
	textFig = Shape::createRect(400, mediaHeight + border*2 );
	textFig->setFillColor(0, 0, 0, 0.8);
	textFig->setPosition(mediaWidth + border * 2, 0);

	//Textbox
	ci::TextBox ciTextBox = ci::TextBox();
	//auto textB = po::scene::TextBox::create(ciTextBox);
	ciTextBox.size(300, 500);
	ciTextBox.color(ci::Color(1, 1, 1));
	ciTextBox.alignment(ci::TextBox::Alignment::LEFT);
	ciTextBox.font(ci::Font("Arial", 20));
	//Headerbox
	ci::TextBox ciHeaderBox = ci::TextBox();
	ciHeaderBox.size(300, mediaHeight*0.2);
	ciHeaderBox.color(ci::Color(1, 1, 1));
	ciHeaderBox.alignment(ci::TextBox::Alignment::CENTER);
	ciHeaderBox.font(ci::Font("Arial", 30));

	ciTextBox.text(_text_se);
	textContentS = po::scene::TextBox::create(ciTextBox);
	textContentS->setPosition(mediaWidth + border * 6, mediaHeight*0.2 + border);
	ciTextBox.text(_text_en);
	textContentE = po::scene::TextBox::create(ciTextBox);
	textContentE->setPosition(mediaWidth + border * 6, mediaHeight*0.2 + border);

	ciHeaderBox.text(_header_se);
	textHeaderS = po::scene::TextBox::create(ciHeaderBox);
	textHeaderS->setPosition(mediaWidth + border * 2, mediaHeight*0.08);
	ciHeaderBox.text(_header_en);
	textHeaderE = po::scene::TextBox::create(ciHeaderBox);
	textHeaderE->setPosition(mediaWidth + border * 2, mediaHeight*0.08);

	//Button created from texture.
	buttonImgS = ci::gl::Texture::create(ci::loadImage(ci::app::loadAsset("swe_eng_button.png")));
	buttonImgE = ci::gl::Texture::create(ci::loadImage(ci::app::loadAsset("eng_swe_button.png")));
	float scaleWidth = mediaWidth / (buttonImgS->getWidth() * 8);
	float scaleHeight = mediaHeight / (buttonImgS->getHeight() * 10);
	buttonScale = ci::vec2(scaleWidth, scaleHeight);
	buttonTextur = Shape::createRect(buttonImgS->getWidth(), buttonImgS->getHeight());
	buttonTextur->setTexture(buttonImgS);
	buttonTextur->setScale(buttonScale.x, buttonScale.y);
	//butTextur->setAlpha(0.8f);
	buttonTextur->setPosition(mediaWidth + border * 2, mediaHeight + border * 2 - buttonTextur->getScaledHeight());

}

void VirtualCard::handleButtonTouches(po::scene::TouchEvent event) {
	if (touchInButton(event) && textVisible)
	{
		//console() << "X = " << event.getLocalPos().x << ", Y =" << event.getLocalPos().y << std::endl;
		if (textSWE)
		{
			textContentS->setVisible(false);
			textContentE->setVisible(true);
			textHeaderS->setVisible(false);
			textHeaderE->setVisible(true);
			buttonTextur->setTexture(buttonImgE);
			
			textSWE = false;
		}
		else
		{
			textContentS->setVisible(true);
			textContentE->setVisible(false);
			textHeaderS->setVisible(true);
			textHeaderE->setVisible(false);
			buttonTextur->setTexture(buttonImgS);

			textSWE = true;
		}
	}
	else if (textVisible)
	{
		textFig->setVisible(false);
		textContentS->setVisible(false);
		textContentE->setVisible(false);
		textHeaderS->setVisible(false);
		textHeaderE->setVisible(false);
		buttonTextur->setVisible(false);

		textVisible = false;
	}
	else
	{
		textFig->setVisible(true);
		textContentS->setVisible(true);
		textHeaderS->setVisible(true);
		buttonTextur->setVisible(true);

		textVisible = true;
	}
}



bool VirtualCard::doubleTouch(po::scene::TouchEvent event)
{
	if (time_checker) {
		time1 = getElapsedSeconds();
	}
	else if (time_checker != true) {
		time2 = getElapsedSeconds();
	}
	if (time2 - time1 < 0.5 && time_checker != true) {
		time_checker = true;
		return true;
	}
	else
		if (time_checker) {
			time_checker = false;
		}
		else
			time_checker = true;
		
	return false;
}

void VirtualCard::applyForce(ci::vec2 force)
{
	ci::vec2 f = force / mass;
	acceleration += f;
	//ci::app::console() << acceleration.x << "  " << acceleration.y << std::endl;
}


void VirtualCard::setRcPos(ci::vec2 rcp)
{
	realCardPos = rcp;
}

float VirtualCard::mag(float x, float y)
{
	return sqrt(x*x + y*y);
}

ci::vec2 VirtualCard::limit(ci::vec2 v, float max)
{
	if (mag(v.x, v.y) > max)
	{
		v = normalize(v);
		return v*max;
	}
	else
	{
		return v;
	}
}


ci::vec2 VirtualCard::separate(std::vector<VirtualCardRef>& v)
{
	float desired_separate = 350;
	ci::vec2 sum;
	int counter = 0;

	for (int i = 0; i < v.size(); i++) {
		float d = mag(getPosition().x - v[i]->getPosition().x, getPosition().y - v[i]->getPosition().y);
		if (d > 0 && d < desired_separate) {
			ci::vec2 diff = getPosition() - v[i]->getPosition();
			diff = normalize(diff);
			//diff = diff / d;
			sum += diff;
			counter++;
		}
	}
	if (counter < 0) {
        velocity *= 0;
	}
	else
        sum = limit(sum, topspeed);
        ci::vec2 steer = sum - velocity;
        steer = limit(steer, maxforce);
        return steer;
}


void VirtualCard::update() {
	time3 = ci::app::getElapsedSeconds();
	//Attraction v1
    
	if (!mIsPressed) {
		ci::vec2 direction = ci::vec2(getPosition().x - realCardPos.x, getPosition().y - realCardPos.y);
		//ci::app::console() << direction.x << "  " << direction.y << std::endl;
        
        if (time3 - end > 3) //When 3 seconds have elapsed the VC will start to move towards the RC again
		{
			if (mag(direction.x, direction.y) > 150) {
				velocity += acceleration;
				setPosition(getPosition().x + velocity.x, getPosition().y + velocity.y);

			}
			/*else if (mag(direction.x, direction.y) <= 400)
			{
			velocity -= acceleration;
			if (mag(velocity.x, velocity.y) < 0.1)
			{
			velocity *= 0;
			}
			}*/
		}
	}
	acceleration *= 0;

	if (mIsPressed)
		velocity *= 0;
}
