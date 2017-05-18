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

    track.setup();
   // track.update();
    //track.setCorners();

    
     // INFO:
     //This works but we have alot of cards!
     //I created a demo2.xml containing all cards with images but no videos, but the images are not added to the repo
     //Good to know: inside RealCard.cpp the you also have to write the name of the xml-file, they are not liked yet
	
	//initStandby();
	
    std::vector<std::string> categories;
    uniqueCategories("demo.xml", categories);
    std::vector<std::vector<VirtualCardRef>> x(categories.size());
    loadXML("demo.xml", x, categories);



     for(int i = 0; i<categories.size(); i++)
     {
	 
         rcards.push_back(RealCard::create(categories[i], i, x[i]));
         rcards[i]->setPosition(i*300, i*100);
         //rcards[i]->setVisible(false); //Screen should be empty at the start
         addChild(rcards[i]);
         rcards[i]->setup(categories[i], i, x[i]);
         idCategories.insert(pair<int, string>(i, categories[i]));
     }
	 
    
	/*
    RealCardRef ref = RealCard::create("livsprocesser",2);
    ref->setPosition(500, 300);
    addChild(ref);
    RealCardRef ref2 = RealCard::create("celler",3);
    ref2->setPosition(500, 300);
    addChild(ref2);
    */
	
	

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

	// Main Circle
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
	standbyContent->setVisible(false);
	standByFig = Shape::createCircle(400);
	standByFig->setFillColor(0, 0, 0.7, 0.8);
	standByFig->setPosition(550, 100);
	addChild(standByFig);
	standByFig->setVisible(false);



	// small Circle
	
	std::string standbyText2 = "Project in !\n Media Technology and Engineering!";
	ci::TextBox TextBox2 = ci::TextBox();
	TextBox2.size(100, 100);
	TextBox2.color(ci::Color(1, 1, 1));
	TextBox2.text(standbyText2);
	TextBox2.alignment(ci::TextBox::Alignment::CENTER);
	TextBox2.font(ci::Font("Arial", 15));

	standbyContent2 = po::scene::TextBox::create(TextBox2);
	standbyContent2->setPosition(1300, 550);
	addChild(standbyContent2);
	standbyContent2->setVisible(false);
	standByFig2 = Shape::createCircle(100);
	standByFig2->setFillColor(0, 0, 1, 0.8);
	standByFig2->setPosition(1300, 550);
	addChild(standByFig2);
	standByFig2->setVisible(false);
	

	// Textures
	auto mbaseShapex = Shape::createRect(img1->getWidth()*0.2, img1->getHeight()*0.2);
	mbaseShapex->setTexture(img1);
	mbaseShapex->setPosition(500, 500);
	standbyShape1 = mbaseShapex;
	addChild(standbyShape1);
	standbyShape1->setVisible(false);

	auto mbaseShapey = Shape::createRect(img2->getWidth()*0.2, img2->getHeight()*0.2);
	mbaseShapey->setTexture(img2);
	mbaseShapey->setPosition(100, 500);
	standbyShape2 = mbaseShapey;
	addChild(standbyShape2);
	standbyShape2->setVisible(false);

	auto mbaseShapez = Shape::createRect(img4->getWidth()*0.2, img4->getHeight()*0.2);
	mbaseShapez->setTexture(img1);
	mbaseShapez->setPosition(1000, 500);
	standbyShape3 = mbaseShapez;
	addChild(standbyShape3);
	standbyShape3->setVisible(false);


	ci::app::timeline().apply(&standbyShape1->getPositionAnim(), ci::vec2(-standbyShape1->getPosition().x / 10, standbyShape1->getHeight() / 10), 10.0f).easeFn(ci::EaseInSine()).loop();
	ci::app::timeline().apply(&standbyShape2->getPositionAnim(), ci::vec2(standbyShape2->getPosition().x, -standbyShape2->getHeight()), 10.0f).easeFn(ci::EaseInSine()).loop();
	ci::app::timeline().apply(&standbyShape3->getPositionAnim(), ci::vec2(standbyShape3->getPosition().x, standbyShape3->getHeight() / 100), 10.0f).easeFn(ci::EaseInSine()).loop();



}

void MicroCosmos::invisibleStandby() {
	standbyContent->setVisible(false);
	standbyShape1->setVisible(false);
	standbyShape2->setVisible(false);
	standbyShape3->setVisible(false);
	standByFig->setVisible(false);
	standByFig2->setVisible(false);
	standbyContent2->setVisible(false);
}

void MicroCosmos::visibleStandby() {
	standbyContent->setVisible(true);
	standbyShape1->setVisible(true);
	standbyShape2->setVisible(true);
	standbyShape3->setVisible(true);
	standByFig->setVisible(true);
	standByFig2->setVisible(true);
	standbyContent2->setVisible(true);


}

void MicroCosmos::update() {
    track.update();
    for (int i = 0; i < rcards.size(); ++i) {
        if(rcards[i]->get_ID() != 0) {
            rcards[i]->setV(false);
        }else {
            rcards[i]->setV(true);
            std::cout << "pos: " << track.getPosMarker(rcards[i]->get_ID() + 4) << " / real: "
                      << track.getScreenCoordinates(track.getPosMarker(rcards[i]->get_ID() + 4)) << std::endl;
            rcards[i]->setPosition(track.getScreenCoordinates(track.getPosMarker(rcards[i]->get_ID() + 4)).x*1577,track.getScreenCoordinates(track.getPosMarker(rcards[i]->get_ID() + 4)).y*1577 );
        }

    }


    //rcards[0]->setV(true);

    std::cout << "pos: " << pos << " / real: " << realPos << std::endl;
    //rcards[0]->setPosition(realPos);

    /*
    for( int i = 0; i < rcards.size(); i++) {
        //std::cout << rcards[i]->get_ID();
        //std::cout << pos << std::endl;
if(rcards[i]->get_ID()  == 0) {
    pos = track.getPosMarker(rcards[i]->get_ID() + 4);
    //std::cout << pos << " / " << rcards[i]->get_ID() + 4 << std::endl;

    if (pos.x > 0 && pos.y > 0) {
        realPos = track.getScreenCoordinates(pos);
        rcards[i]->setV(true);
        rcards[i]->setPosition(realPos.x, realPos.y);
        //std::cout << "rpos: " << realPos ;
        //std::cout << " pos: " << rcards[i]->getPosition();
        //std::cout << "gfghkfghjf " << rcards[i]->getPosition() << std::endl;
    } else {
        rcards[i]->setV(false);
        //std::cout << pos << std::endl;
    }
}

     */



}


void MicroCosmos::loadXML(const char *file, std::vector<std::vector<VirtualCardRef>> &cards, std::vector<std::string> category)
{
	std::string path;
	std::vector<std::string> categories;
	std::string header_se;
	std::string text_se;
	std::string header_en;
	std::string text_en;
	//float scale;

	//std::vector<std::string> categories2 = {"proteiner", "livsprocesser", "sjukdomar", "gener", "molekyler"};
	//std::vector<std::vector<VirtualCardRef>> rCards(categories2.size() );

	ci::XmlTree doc(ci::app::loadAsset(file));

	/*for (ci::XmlTree::Iter xy = doc.begin("info/categories")->begin("category") ; xy != xy->end(); ++xy){
        console() << xy->getAttribute("name").getValue() << std::endl;
        console() << "gjk" << std::endl;
    }*/

	for (ci::XmlTree::Iter track = doc.begin("content/media"); track != doc.end(); ++track) {
        categories.clear();
		//console() << track->getAttribute("path").getValue() << endl;
		path = track->getAttribute("path").getValue();
		//ci::app::console() << path << std::endl;
		//ci::app::console() << track->getAttribute("scale_exp").getValue() << std::endl;
		//scale = std::atof(track->getAttribute("scale_exp").getValue());
		for (ci::XmlTree::Iter cat = track->begin("category"); cat != track->end(); ++cat) {
			//console() << cat->getAttribute("name").getValue() << endl;
            categories.push_back(cat->getAttribute("name").getValue());
			//ci::app::console() << cat->getAttribute("name").getValue() << std::endl;
		}
			//console() << track->getChild("se/header").getValue() << endl;
			header_se = track->getChild("se/header").getValue();
			//ci::app::console() << header_se << std::endl;
			//console() << track->getChild("se/text").getValue() << endl;
			text_se = track->getChild("se/text").getValue();
			//ci::app::console() << text_se << std::endl;
			//console() << track->getChild("en/header").getValue() << endl;
			header_en = track->getChild("en/header").getValue();
			//ci::app::console() << header_en << std::endl;
			//console() << track->getChild("en/text").getValue() << endl;
			text_en = track->getChild("en/text").getValue();
			//ci::app::console() << text_en << std::endl;
			//VirtualCardRef ref = VirtualCard::create(ci::Color(1, 1, 1), path, 0.6f, categories, header_se, text_se, header_en, text_en);
			for (int i = 0; i < categories.size() ; ++i) {
				std::cout << "ca: "<< categories.size() << std::endl;
				for (int j = 0; j < category.size(); ++j){
					if( categories[i] == category[j]){
						//std::cout << "fhg" << std::endl;
						//std::cout << j <<": " << categories2[j] << std::endl;
						VirtualCardRef ref = VirtualCard::create(ci::Color(1, 1, 1), path, 0.6f, categories, header_se, text_se, header_en, text_en);
                        cards[j].push_back( ref);
						break;
					}
				}
			}
			//ci::app::console() << std::endl;
	}

	std::cout << cards.size() << std::endl;
    //cards = rCards;
}

