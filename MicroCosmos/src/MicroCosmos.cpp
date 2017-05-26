//
//  MicroCosmos.cpp
//  MicroCosmos
//
//  Created by Johan Eriksson on 2017-04-22.
//
//

#include "MicroCosmos.hpp"

using namespace po::scene;

MicroCosmosRef MicroCosmos::create() {
    MicroCosmosRef node (new MicroCosmos());
    node -> setup();
    return node;
}

void MicroCosmos::setup(){
    tracking_.setup();
    /*
     *INFO: Good to know: inside RealCard.cpp the you also have to write the name of the XML-file, they are not liked yet
     */
    std::vector<std::string> categories;
    uniqueCategories("demo.xml", categories);
    std::vector<std::vector<VirtualCardRef>> x(categories.size());
    loadXML("demo.xml", x, categories);

    for(int i = 0; i<categories.size(); i++) {
        realcards_.push_back(RealCard::create(categories[i], i , x[i]));
        //realcards_[i]->setPosition(i*300, i*100);
        //realcards_[i]->setVisible(false); //Screen should be empty at the start
        addChild(realcards_[i]);
        realcards_[i]->setup(categories[i], i ,x[i]);
        id_categories_.insert(pair<int, string>(i, categories[i]));
    }
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
bool MicroCosmos::stringInVector(std::string category, std::vector<std::string> categories) {
    
    for (int i = 0; i < categories.size(); ++i) {
        if(categories[i]==category)
            return true;
    }
    return false;
}


void MicroCosmos::onTouchDown(po::scene::TouchEvent &event) {
    touchid_.push_back(event.getId());
    events_.push_back(event);
    
   /* //if three fingers(or more) are placed on the screen, a realcard is shown at that position
    if (touchid_.size() >= 3) {
        realcards_[1]->setVisible(true);
        realcards_[1]->setPosition(events_[touchid_.size() - 1].getWindowPos());
    }*/
}


void MicroCosmos::onTouchUp(po::scene::TouchEvent &event) {
    removeTouchId(event.getId());
    removeTouchEvent(event);
}


void MicroCosmos::removeTouchId(uint32_t id) {
    for (int i = 0; i<touchid_.size(); ++i) {
        if (touchid_[i] == id) {
            touchid_.erase(touchid_.begin() + i);
            std::cout << "removing id " << id << std::endl;
        }
    }
}


void MicroCosmos::removeTouchEvent(po::scene::TouchEvent tEvent) {
    for (int i = 0; i<events_.size(); ++i) {
        if (events_[i].getId() == tEvent.getId()) {
            events_.erase(events_.begin() + i);
        }
    }
}


void MicroCosmos::update() {

	tracking_.update();

	for (int i = 0; i < realcards_.size(); ++i) {
		if (realcards_[i]->getId() != 0) {
			realcards_[i]->setV(false);
		}
		else {
			/*//BASED ON TRACKING [ use this version for VR-LAB]
			if (tracking_.getPosMarker(realcards_[i]->get_ID() + 4)[0] >= 0 && tracking_.getPosMarker(realcards_[i]->get_ID() + 4)[1] >= 0) {

				realcards_[i]->setV(true);
				//std::cout << "pos_: " << tracking_.getPosMarker(realcards_[i]->get_ID() + 4) << " / real: "
				//         << tracking_.getScreenCoordinates(tracking_.getPosMarker(realcards_[i]->get_ID() + 4)) << std::endl;
				realcards_[i]->setPosition(tracking_.getScreenCoordinates(tracking_.getPosMarker(realcards_[i]->get_ID() + 4)).x * 1577,
					tracking_.getScreenCoordinates(tracking_.getPosMarker(realcards_[i]->getId() + 4)).y * 1577);
				realcards_[i]->initVcards(realcards_[i]->getPosition());

			}//BASED ON TRACKING ends here*/

			//HARDCODED CARD VERSION [ use this version when coding not at VR-LAB]	
			if (true){
			realcards_[i]->setV(true);
			realcards_[i]->setPosition(700, 300);
			realcards_[i]->initVcards(realcards_[i]->getPosition());
			} //HARDCODED CARD VERSION ends here


			else {
				realcards_[i]->setV(false);
				realcards_[i]->resetInitiation();
			}
		}
	}
}


void MicroCosmos::loadXML(const char *file, std::vector<std::vector<VirtualCardRef>> &cards, std::vector<std::string> category) {
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
        //console() << tracking_->getAttribute("path").getValue() << endl;
        path = track->getAttribute("path").getValue();
        //ci::app::console() << path << std::endl;
        //ci::app::console() << tracking_->getAttribute("scale_exp").getValue() << std::endl;
        //scale = std::atof(tracking_->getAttribute("scale_exp").getValue());
        for (ci::XmlTree::Iter cat = track->begin("category"); cat != track->end(); ++cat) {
            //console() << cat->getAttribute("name").getValue() << endl;
            categories.push_back(cat->getAttribute("name").getValue());
            //ci::app::console() << cat->getAttribute("name").getValue() << std::endl;
        }
        //console() << tracking_->getChild("se/header").getValue() << endl;
        header_se = track->getChild("se/header").getValue();
        //ci::app::console() << header_se << std::endl;
        //console() << tracking_->getChild("se/text").getValue() << endl;
        text_se = track->getChild("se/text").getValue();
        //ci::app::console() << text_se << std::endl;
        //console() << tracking_->getChild("en/header").getValue() << endl;
        header_en = track->getChild("en/header").getValue();
        //ci::app::console() << header_en << std::endl;
        //console() << tracking_->getChild("en/text").getValue() << endl;
        text_en = track->getChild("en/text").getValue();
        //ci::app::console() << text_en << std::endl;
        //VirtualCardRef ref = VirtualCard::create(ci::Color(1, 1, 1), path, 0.6f, categories, header_se, text_se, header_en, text_en);
        for (int i = 0; i < categories.size() ; ++i) {
            //std::cout << "ca: "<< categories.size() << std::endl;
            for (int j = 0; j < category.size(); ++j){
                if( categories[i] == category[j]){
                    //std::cout << "fhg" << std::endl;
                    //std::cout << j <<": " << categories2[j] << std::endl;
                    VirtualCardRef ref = VirtualCard::create(ci::Color(1, 1, 1), path, 0.2f, categories, header_se, text_se, header_en, text_en);
                    cards[j].push_back( ref);
                    break;
                }
            }
        }
        //ci::app::console() << std::endl;
    }
    //cards = rCards;
}

