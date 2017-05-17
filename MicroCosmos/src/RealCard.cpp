#include "RealCard.h"

#include "poShape.h"

using namespace po::scene;

RealCardRef RealCard::create(std::string category, int id, std::vector<VirtualCardRef> cards) {
    
    RealCardRef node(new RealCard()); //Using a default constructor for the moment
    //node->setup(category,id, cards); //Not neccessary to pass var category if member of RealCard
    return node;
}

void RealCard::setup(std::string category, int id, std::vector<VirtualCardRef> cards)
{
    
    
    
    
    //creates virtualCards and save the refs to them in the vector vCards
    vCards = cards;
    int nrOfVirtcards = vCards.size();
	ID = id;
    float radius = 300;
    setName(category);
	Category = category;





    //position the virtual cards around the real card and add as children
    for (int i = 0; i<nrOfVirtcards; ++i)
    {
        vCards[i]->setPosition(ci::vec2(radius * cos(6.28 * i/nrOfVirtcards), radius * sin(6.28 * i/nrOfVirtcards)));
        getParent()->addChild(vCards[i]);
        vCards[i]->setName(category+"_"+vCards[i]->getName());
        std::cout << vCards[i]->getName() << std::endl;
        //vCards[i]->setVisible(false);
        //std::cout << "hgk" << std::endl;
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

<<<<<<< HEAD
string RealCard::get_Category() {

	return Category;
}
=======

void RealCard::setV(bool v){
    setVisible(v);
    for (int j = 0; j < vCards.size(); ++j) {
        vCards[j]->setVisible(v);
    }
}
>>>>>>> origin/master
