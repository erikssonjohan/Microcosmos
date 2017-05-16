#include "RealCard.h"

#include "poShape.h"

using namespace po::scene;

RealCardRef RealCard::create(std::string category, int id, std::vector<VirtualCardRef> cards) {
    
    RealCardRef node(new RealCard()); //Using a default constructor for the moment
    node->setup(category,id, cards); //Not neccessary to pass var category if member of RealCard
    return node;
}

void RealCard::setup(std::string category, int id, std::vector<VirtualCardRef> cards)
{
    
    
    
    
    //creates virtualCards and save the refs to them in the vector vCards
    //loadXML("demo.xml", vCards, category);
    vCards = cards;
    int nrOfVirtcards = vCards.size();
	ID = id;
    float radius = 300;

    
    //position the virtual cards around the real card and add as children
    for (int i = 0; i<nrOfVirtcards; ++i)
    {
        vCards[i]->setPosition(ci::vec2(radius * cos(6.28 * i/nrOfVirtcards), radius * sin(6.28 * i/nrOfVirtcards)));
        addChild(vCards[i]);
    }
    

	circle = Shape::createCircle(400);
	circle->setFillColor(0, 1, 0, 1);
	circle->setPosition(0,0);
	addChild(circle);
	circle->setVisible(true);

    //std::cout << "nrOfVirtcards: " << nrOfVirtcards << std::endl;
    //std::cout << category << std::endl;
}

int RealCard::get_ID() {


	return ID;

}
