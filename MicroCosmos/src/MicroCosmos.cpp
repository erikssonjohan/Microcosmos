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
    
   /* 
   // The same function will be used for RealCArds but the vector will not be created with loadXML
   loadXML("demo.xml", cards);
    
    for (int i = 0; i<cards.size(); ++i) {
        cards[i]->setPosition(ci::vec2(cards[i]->x, cards[i]->y));
        addChild(cards[i]);        
        std::cout << "add" << std::endl;
    }
    */
	RealCardRef ref = RealCard::create("proteiner");
	//ref->setPosition(500, 500);
	addChild(ref);
    
    
}

//Will add a function that finds all the categories and calls RealCard::create()
