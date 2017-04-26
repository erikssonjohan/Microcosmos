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
     
     /*
     std::vector<std::string> categories;
     uniqueCategories("demo.xml", categories);
     
     for(int i = 0; i<categories.size(); i++)
     {
     rcards.push_back(RealCard::create(categories[i]));
     rcards[i]->setPosition(i*300, i*100);
     addChild(rcards[i]);
     }
    */
    
    RealCardRef ref = RealCard::create("gener");
    ref->setPosition(500, 300);
    addChild(ref);
    
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

// getSignal(po::scene::TouchEvent::BEGAN).connect(std::bind(&MicroCosmos::onTouchDown, this, std::placeholders::_1));
// getSignal(po::scene::TouchEvent::ENDED).connect(std::bind(&MicroCosmos::onTouchUp, this, std::placeholders::_1));



void MicroCosmos::onTouchDown(po::scene::TouchEvent &event){
    
    
    //touch down
    
    
    
}

void MicroCosmos::onTouchUp(po::scene::TouchEvent &event) {
    
    // touch up
    
}

