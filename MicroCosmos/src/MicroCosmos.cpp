//
//  MicroCosmos.cpp
//  MicroCosmos
//
//  Created by Johan Eriksson on 2017-04-22.
//
//

#include "MicroCosmos.hpp"

using namespace po::scene;

MicroCosmosRef MicroCosmos::create(){
    MicroCosmosRef node (new MicroCosmos());
    node -> setup();
    return node;
}

void MicroCosmos::setup(){
    
    
     // INFO:
     //This works but we have alot of cards!
     //I created a demo2.xml containing all cards with images but no videos, but the images are not added to the repo
     //Good to know: inside RealCard.cpp the you also have to write the name of the xml-file, they are not liked yet
	
	initStandby();
	
     std::vector<std::string> categories;
     uniqueCategories("demo.xml", categories);
     
     for(int i = 0; i<categories.size(); i++)
     {
     rcards.push_back(RealCard::create(categories[i]));
     rcards[i]->setPosition(i*300, i*100);
	 rcards[i]->setVisible(false); //Screen should be empty at the start 
     addChild(rcards[i]);
     }
    
	
    RealCardRef ref = RealCard::create("");
    ref->setPosition(500, 300);
    addChild(ref);
    
	
	

	 //getSignal(po::scene::TouchEvent::BEGAN).connect(std::bind(&MicroCosmos::onTouchDown, this, std::placeholders::_1));
	 //getSignal(po::scene::TouchEvent::ENDED).connect(std::bind(&MicroCosmos::onTouchUp, this, std::placeholders::_1));

	
}

//Function that finds all the categories and calls RealCard::create()
void MicroCosmos::uniqueCategories(const char *file, std::vector<std::string> &categories){
    
    ci::XmlTree doc(ci::app::loadAsset(file));
    
    //std::cout << "Found following categories: " << endl;
    for (ci::XmlTree::Iter track = doc.begin("content/media"); track != doc.end(); ++track) {
        for (ci::XmlTree::Iter cat = track->begin("category"); cat != track->end(); ++cat) {
            if(!MicroCosmos::stringInVector(cat->getAttribute("name").getValue(), categories)){
                categories.push_back(cat->getAttribute("name").getValue());
                //std::cout << cat->getAttribute("name").getValue() << endl;
            }
        }
    }
}

//used in uniqueCategories(...)
bool MicroCosmos::stringInVector(std::string category, std::vector<std::string> categories){
    
    for (int i = 0; i < categories.size(); ++i) {
        if(categories[i]==category)
            return true;
    }
    return false;
}



void MicroCosmos::onTouchDown(po::scene::TouchEvent &event){
    
	
	touchId.push_back(event.getId());
	events.push_back(event);

	if (touchId.size() >= 3)//if three fingers(or more) are placed on the screen, a realcard is shown at that position
	{
		rcards[1]->setVisible(true);
		rcards[1]->setPosition(events[touchId.size() - 1].getWindowPos());
		invisibleStandby();
	}
	
     
}

void MicroCosmos::onTouchUp(po::scene::TouchEvent &event) {
    
		removeTouchId(event.getId());
		removeTouchEvent(event);

	}
    


void MicroCosmos::removeTouchId(uint32_t id) {
	for (int i = 0; i<touchId.size(); ++i) {
		if (touchId[i] == id) {
			touchId.erase(touchId.begin() + i);
			std::cout << "removing id " << id << std::endl;
		}
	}

}

void MicroCosmos::removeTouchEvent(po::scene::TouchEvent tEvent) {
	for (int i = 0; i<events.size(); ++i) {
		if (events[i].getId() == tEvent.getId()) {
			events.erase(events.begin() + i);
		}
	}
}

void MicroCosmos::initStandby() {

	std::string standbyText = "WELCOME TO MICROCOSMOS!\n\n PLEASE PUT A CARD ON THE TABLE!";
	ci::TextBox TextBox = ci::TextBox();
	TextBox.size(300, 500);
	TextBox.color(ci::Color(1, 1, 1));
	TextBox.text(standbyText);
	TextBox.alignment(ci::TextBox::Alignment::CENTER);
	TextBox.font(ci::Font("Arial", 45));
	standbyContent = po::scene::TextBox::create(TextBox);
	standbyContent->setPosition(600, 50);
	addChild(standbyContent);



	// Textures
	auto mbaseShapex = Shape::createRect(img1->getWidth()*0.2, img1->getHeight()*0.2);
	mbaseShapex->setTexture(img1);
	mbaseShapex->setPosition(500, 500);
	standbyShape1 = mbaseShapex;
	addChild(standbyShape1);

	auto mbaseShapey = Shape::createRect(img2->getWidth()*0.2, img2->getHeight()*0.2);
	mbaseShapey->setTexture(img2);
	mbaseShapey->setPosition(100, 500);
	standbyShape2 = mbaseShapey;
	addChild(standbyShape2);

	auto mbaseShapez = Shape::createRect(img4->getWidth()*0.2, img4->getHeight()*0.2);
	mbaseShapez->setTexture(img1);
	mbaseShapez->setPosition(1200, 500);
	standbyShape3 = mbaseShapez;
	addChild(standbyShape3);



	ci::app::timeline().apply(&standbyShape1->getPositionAnim(), ci::vec2(-standbyShape1->getPosition().x / 10, standbyShape1->getHeight() / 10), 10.0f).easeFn(ci::EaseInSine()).loop();
	ci::app::timeline().apply(&standbyShape2->getPositionAnim(), ci::vec2(standbyShape2->getPosition().x, -standbyShape2->getHeight()), 10.0f).easeFn(ci::EaseInSine()).loop();
	ci::app::timeline().apply(&standbyShape3->getPositionAnim(), ci::vec2(standbyShape3->getPosition().x, standbyShape3->getHeight() / 100), 10.0f).easeFn(ci::EaseInSine()).loop();



}

void MicroCosmos::invisibleStandby() {
	standbyContent->setVisible(false);
	standbyShape1->setVisible(false);
	standbyShape2->setVisible(false);
	standbyShape3->setVisible(false);
	setVisible(true);
}

void MicroCosmos::visibleStandby() {
	standbyContent->setVisible(true);
	standbyShape1->setVisible(true);
	standbyShape2->setVisible(true);
	standbyShape3->setVisible(true);


}

void MicroCosmos::update() {
	time2 = getElapsedSeconds();
	if (time2 - time1 > 10)
		visibleStandby();

	if (foundRealCard)
		invisibleStandby();

}