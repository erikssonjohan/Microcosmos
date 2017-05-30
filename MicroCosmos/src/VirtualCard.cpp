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
    
    //Sets scale to a maximum height of 100 pixels
	scale_ = 100 / media_height_;
    setScale(scale_);

	getSignal(po::scene::TouchEvent::BEGAN_INSIDE).connect(std::bind(&VirtualCard::onTouchDown, this, std::placeholders::_1));
	getSignal(po::scene::TouchEvent::MOVED_INSIDE).connect(std::bind(&VirtualCard::onTouchDragged, this, std::placeholders::_1));
	getSignal(po::scene::TouchEvent::MOVED).connect(std::bind(&VirtualCard::onTouchDragged, this, std::placeholders::_1));
	getSignal(po::scene::TouchEvent::ENDED_INSIDE).connect(std::bind(&VirtualCard::onTouchUp, this, std::placeholders::_1));
	getSignal(po::scene::TouchEvent::ENDED).connect(std::bind(&VirtualCard::onTouchUp, this, std::placeholders::_1));
}

void VirtualCard::onTouchDown(po::scene::TouchEvent &event) {
	start_ = ci::app::getElapsedSeconds();
	
	//.... What should the doubletouch do?? Scales down and up the virtual cards to max/min
	/*if (doubleTouch(event))  {

		if (!doubleCheck) {
			scale_ = (500 / media_height_);
			doubleCheck = true;
		}
		else {
			scale_ = (100 / media_height_);
			doubleCheck = false;
		}
		setScale(scale_);
	}
	*/
	if (!idInCard(event.getId())) {
		std::cout << "tryck " << event.getId() << std::endl;
		mIsPressed = true;
		touch_id_.push_back(event.getId());
		events_.push_back(event);

		pPos_.push_back(event.getWindowPos());

		// Moves the card to drawn at the front
		getParent()->moveChildToFront(getParent()->getChildByName(this->getName()));

		if (touch_id_.size() == 1) {
			// Update the position of the card
			mInitialPos_ = getPosition();
			mStartPos_ = getParent()->windowToLocal(event.getWindowPos());
			mEndPos_ = getParent()->windowToLocal(event.getWindowPos());
		}
	}
}

//	Touch dragged event handler
void VirtualCard::onTouchDragged(po::scene::TouchEvent &event) {
	if (idInCard(event.getId()) && touch_id_[0] == event.getId()) {
		mEndPos_ = getParent()->windowToLocal(event.getWindowPos());
        //ci::vec2 newPosition = (mInitialPos + (mEndPos - mStartPos));
        ci::vec2 newPosition = getPosition();
         newPosition.x += events_[0].getWindowPos().x-pPos_[0].x;
        newPosition.y += events_[0].getWindowPos().y-pPos_[0].y;
		setPosition(newPosition);

	}
	if (events_.size() >= 2) {
		scale(events_[0].getWindowPos(), pPos_[0], events_[1].getWindowPos(), pPos_[1]);
		setScale(scale_);
        touchRotate(events_[0].getWindowPos(), pPos_[0], events_[1].getWindowPos(), pPos_[1]);
        setRotation(angle_);
	}
	for (int i = 0; i<events_.size(); ++i) {
		if (events_[i].getId() == event.getId()) {
			pPos_[i] = events_[i].getWindowPos();
			events_[i] = event;
		}
	}
}

//	Touch up event handler
void VirtualCard::onTouchUp(po::scene::TouchEvent &event) {
	if (idInCard(event.getId()))
	{
		end_ = ci::app::getElapsedSeconds();
		double timeTouched = (end_ - start_);
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
	for (int i = 0; i<touch_id_.size(); ++i) {
		if (touch_id_[i] == id) {
			//std::cout << id <<" is in card" << std::endl;
			return true;
		}
	}
	return false;
}
bool VirtualCard::touchInButton(po::scene::TouchEvent event) {
	if (event.getLocalPos().x >= button_texture_->getPosition().x && event.getLocalPos().x <= (button_texture_->getPosition().x + button_texture_->getScaledWidth()) && event.getLocalPos().y >= button_texture_->getPosition().y && event.getLocalPos().y <= button_texture_->getPosition().y + button_texture_->getScaledHeight()) {
		return true;
	}
	return false;
}


void VirtualCard::removeTouchId(uint32_t id) {
	for (int i = 0; i<touch_id_.size(); ++i) {
		if (touch_id_[i] == id) {
			touch_id_.erase(touch_id_.begin() + i);
			std::cout << "removing id " << id << std::endl;
		}
	}
}

//removes touch id from card
void VirtualCard::removeTouchEvent(po::scene::TouchEvent tEvent) {
	for (int i = 0; i<events_.size(); ++i) {
		if (events_[i].getId() == tEvent.getId()) {
			events_.erase(events_.begin() + i);
			pPos_.erase(pPos_.begin() + i);
		}
	}
}

void VirtualCard::scale(ci::vec2 pos1, ci::vec2 pPos1, ci::vec2 pos2, ci::vec2 pPos2) {

	float currentDistance = sqrt(pow(pos1[0] - pos2[0], 2) + pow(pos1[1] - pos2[1], 2));
	float previousDistance = sqrt(pow(pPos1[0] - pPos2[0], 2) + pow(pPos1[1] - pPos2[1], 2));

	// Guard against division by zero & nan
	if (previousDistance != 0 && previousDistance == previousDistance) {
		scale_ *= currentDistance / previousDistance;
        
        //Set boundaries of scale for the height of the media between 100 and 500 pixels.
        if(scale_ * media_height_ > 500){
            scale_ = 500/media_height_;
        }
        if(scale_ * media_height_< 100){
            scale_ = 100/media_height_;
        }
	}
}

void VirtualCard::touchRotate(ci::vec2 pos1, ci::vec2 pPos1, ci::vec2 pos2, ci::vec2 pPos2) {
    vec2 a = pos2-pos1;
    vec2 b = pPos2-pPos1;
    a = normalize(a);
    b = normalize(b);

    angle_ += atan2(a.y, a.x)-atan2(b.y, b.x);
    //std::cout << angle_ << std::endl;
}

void VirtualCard::createTextBox() {
	// TODO:: make it less static and might need some fixes. just did it to test, not sure if its the best way // JEx
	textFig_ = Shape::createRect(400, media_height_ + border_*2 );
	textFig_->setFillColor(0, 0, 0, 0.8);
	textFig_->setPosition(media_width_ + border_ * 2, 0);

	//Textbox
	ci::TextBox ciTextBox = ci::TextBox();
	//auto textB = po::scene::TextBox::create(ciTextBox);
	ciTextBox.size(300, 500);
	ciTextBox.color(ci::Color(1, 1, 1));
	ciTextBox.alignment(ci::TextBox::Alignment::LEFT);
	ciTextBox.font(ci::Font("Arial", 32));
	//Headerbox
	ci::TextBox ciHeaderBox = ci::TextBox();
	ciHeaderBox.size(300, media_height_*0.2);
	ciHeaderBox.color(ci::Color(1, 1, 1));
	ciHeaderBox.alignment(ci::TextBox::Alignment::CENTER);
	ciHeaderBox.font(ci::Font("Arial", 36));

	ciTextBox.text(text_se_);
	text_contentS_ = po::scene::TextBox::create(ciTextBox);
	text_contentS_->setPosition(media_width_ + border_ * 6, media_height_*0.2 + border_);
	ciTextBox.text(text_en_);
	text_contentE_ = po::scene::TextBox::create(ciTextBox);
	text_contentE_->setPosition(media_width_ + border_ * 6, media_height_*0.2 + border_);

	ciHeaderBox.text(header_se_);
	text_headerS_ = po::scene::TextBox::create(ciHeaderBox);
	text_headerS_->setPosition(media_width_ + border_ * 2, media_height_*0.04);
	ciHeaderBox.text(header_en_);
	text_headerE_ = po::scene::TextBox::create(ciHeaderBox);
	text_headerE_->setPosition(media_width_ + border_ * 2, media_height_*0.04);

	//Button created from texture.
	button_imgS_ = ci::gl::Texture::create(ci::loadImage(ci::app::loadAsset("swe_eng_button.png")));
	button_imgE_ = ci::gl::Texture::create(ci::loadImage(ci::app::loadAsset("eng_swe_button.png")));
	//float scaleWidth = textFig_->getScaledWidth() / (button_imgS_->getWidth() * 2.0f);
	//float dimensionalScale = (button_imgS_->getWidth() * scaleWidth) /  button_imgS_->getWidth(); //This variable makes sure that the scaling is according to the buttonImg dimensions, which decreases pixelation
	//float scaleHeight = button_imgS_->getHeight() *dimensionalScale;
	float scaleWidth = media_width_ / (button_imgS_->getWidth() * 8);
	float scaleHeight = media_height_ / (button_imgS_->getHeight() * 10);
	button_scale_ = ci::vec2(scaleWidth, scaleHeight);
	button_texture_ = Shape::createRect(button_imgS_->getWidth(), button_imgS_->getHeight());
	button_texture_->setTexture(button_imgS_);
	button_texture_->setScale(button_scale_.x, button_scale_.y);
	//butTextur->setAlpha(0.8f);
	button_texture_->setPosition(media_width_ + border_ * 2, media_height_ + border_ * 2 - button_texture_->getScaledHeight());

}

void VirtualCard::handleButtonTouches(po::scene::TouchEvent event) {
	if (touchInButton(event) && text_visible_)
	{
		//console() << "X = " << event.getLocalPos().x << ", Y =" << event.getLocalPos().y << std::endl;
		if (text_SWE_)
		{
			text_contentS_->setVisible(false);
			text_contentE_->setVisible(true);
			text_headerS_->setVisible(false);
			text_headerE_->setVisible(true);
            button_texture_->setTexture(button_imgE_);
			
			text_SWE_ = false;
		}
		else
		{
			text_contentS_->setVisible(true);
			text_contentE_->setVisible(false);
			text_headerS_->setVisible(true);
			text_headerE_->setVisible(false);
			button_texture_->setTexture(button_imgS_);

			text_SWE_ = true;
		}
	}
	else if (text_visible_)
	{
		textFig_->setVisible(false);
		text_contentS_->setVisible(false);
		text_contentE_->setVisible(false);
		text_headerS_->setVisible(false);
		text_headerE_->setVisible(false);
		button_texture_->setVisible(false);

		text_visible_ = false;
	}
	else
	{
		textFig_->setVisible(true);
		text_contentS_->setVisible(true);
		text_headerS_->setVisible(true);
		button_texture_->setVisible(true);

		text_visible_ = true;
	}
}



bool VirtualCard::doubleTouch(po::scene::TouchEvent event)
{
	if (time_checker_) {
		time1_ = getElapsedSeconds();
	}
	else if (time_checker_ != true) {
		time2_ = getElapsedSeconds();
	}
	if (time2_ - time1_ < 0.5 && time_checker_ != true) {
		time_checker_ = true;
		return true;
	}
	else
		if (time_checker_) {
			time_checker_ = false;
		}
		else
			time_checker_ = true;
		
	return false;
}

void VirtualCard::applyForce(ci::vec2 force) {
	ci::vec2 f = force / mass;
	acceleration_ += f;
	//acceleration_ *= (float)0.6;
	//ci::app::console() << acceleration.x << "  " << acceleration.y << std::endl;
}


void VirtualCard::setRcPos(ci::vec2 rcp) {
	real_card_pos_ = rcp;
}

float VirtualCard::mag(float x, float y) {
	return sqrt(x*x + y*y);
}

ci::vec2 VirtualCard::limit(ci::vec2 v, float max) {
	if (mag(v.x, v.y) > max) {
		v = normalize(v);
		return v*max;
	}
	else {
		return v;
	}
}


ci::vec2 VirtualCard::separate(std::vector<VirtualCardRef>& v) {
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
        velocity_ *= 0;
	}
	else
        sum = limit(sum, top_speed_);
        ci::vec2 steer = sum - velocity_;
        steer = limit(steer, max_force_);
        return steer;
}


void VirtualCard::update() {
	time3_ = ci::app::getElapsedSeconds();
	//Attraction v1
    
	if (!mIsPressed) {
		ci::vec2 direction = ci::vec2(getPosition().x - real_card_pos_.x, getPosition().y - real_card_pos_.y);
		//ci::app::console() << direction.x << "  " << direction.y << std::endl;
        
        if (time3_ - end_ > 3) //When 3 seconds have elapsed the VC will start to move towards the RC again
		{
			if (mag(direction.x, direction.y) > 200) {
				velocity_ += acceleration_;
				velocity_ *= (float)0.95;
				setPosition(getPosition().x + velocity_.x, getPosition().y + velocity_.y);

			}
			else //if (mag(direction.x, direction.y) <= 400)
			{
			//velocity -= acceleration;
			//if (mag(velocity.x, velocity.y) < 0.1)
			//{
				velocity_ = {0,0};
			//}
			}
		}
	}
	acceleration_ *= 0;

	if (mIsPressed)
		velocity_ *= 0;
}
