#include "RealCard.h"

#include "poShape.h"

using namespace po::scene;

RealCardRef RealCard::create(std::string category, int id, std::vector<VirtualCardRef> cards) {
    
    RealCardRef node(new RealCard()); //Using a default constructor for the moment
    //node->setup(category,id, cards); //Not neccessary to pass var category if member of RealCard
    return node;
}

void RealCard::setup(std::string category,int id,std::vector<VirtualCardRef> cards) {
    //creates virtualCards and save the refs to them in the vector vCards
    vCards = cards;
    setName(category);
	Category = category;
    ID = id;

	//Forces
	G = 1;
	mass = 20;

	circle = Shape::createCircle(400);
	circle->setFillColor(0, 1, 0, 1);
	circle->setPosition(0,0);
	addChild(circle);

    setV(false);
}




string RealCard::get_Category() {
	return Category;
}


void RealCard::setV(bool v){
    setVisible(v);
    for (int j = 0; j < vCards.size(); ++j) {
        //std::cout  << vCards.size() << getName() << " / " << vCards[j]->getName() << std::endl;
        vCards[j]->setVisible(v);
    }
}

void RealCard::initVcards(glm::vec2 rCardPos)
{
	if (!rCardInitiated)
	{
		int nrOfVirtcards = vCards.size();
		const int radius = 20;

		//position the virtual cards around the real card and add as children
		for (int i = 0; i<nrOfVirtcards; ++i)
		{
			vCards[i]->setPosition(ci::vec2(rCardPos.x + radius * cos(2 * M_PI * i / nrOfVirtcards), rCardPos.y + radius * sin(2 * M_PI * i / nrOfVirtcards)));
			getParent()->addChild(vCards[i]);
			vCards[i]->setName(get_Category() + "_" + vCards[i]->getName());
		}
		rCardInitiated = true;
	}


}

void RealCard::resetInitiation()
{
	rCardInitiated = false;
}

int RealCard::get_ID() {
    return ID;
}


bool RealCard::findTouchpoints(){
    
    //The card has three points forminng a triangle with two different sidelengths
    float SCALE = 1.0; //To match values to screen koordinates
    float CARD_D1 = 56 * SCALE; //one shorter (56mm)
    float CARD_D2 = 66 * SCALE; //two longer (66mm)
    //float CARD_RADIUS = 36.5 * SCALE; //from card center to center of leg (36.5mm)
    float CARD_PRECISSION = 25* SCALE; //distances can differ
    po::scene::TouchEvent event = events.back();
    
    for(int i=0; i<events.size()-1; i++) {
        
        float d1 = length(events[i].getWindowPos() - event.getWindowPos());
        std::cout << "d1 = " << d1 << endl;
        
        //test the rest of the touchpoints to find last point
        if(abs(d1 - CARD_D1) < CARD_PRECISSION) {
            //Shorter distance found -> both point should have longer length to third point
            std::cout << "Found shorter distance!" << std::endl;
            for(int j=i+1; j<events.size()-1; j++) {
                float d2 = length(events[j].getWindowPos() - event.getWindowPos());
                float d3 = length(events[j].getWindowPos() - events[i].getWindowPos());
                
                if(abs(d2 - CARD_D2)<CARD_PRECISSION && abs(d3 - CARD_D2)<CARD_PRECISSION) {
                    std::cout << "A CARD WAS FOUND!" << std::endl;
                    
                    //One short and one long vector from event
                    vec2 side1 = events[i].getWindowPos() - event.getWindowPos(); //short
                    vec2 side2 = events[j].getWindowPos() - event.getWindowPos(); //long
                    
                    //centerpoint is found by going in the directions of the edge vectors from event corner
                    vec2 centerpoint = event.getWindowPos() + 0.3f*side1 + 0.4f*side2;
                    
                    //if centerpoint matches that of the marker the touchpoints are the table legs
                    if(length(getPosition() - centerpoint) < CARD_PRECISSION) {
                        touchId.push_back(events[j].getId()); //first is sharp edge
                        touchId.push_back(event.getId());
                        touchId.push_back(events[i].getId());
                        return true;
                    }
                }
            }
        }
        
        else if(abs(d1 - CARD_D1) < CARD_PRECISSION) {
            //one longer distance found -> one short and one long left
            cout << "Found one longer distance!" << endl;
            
            for(int j=i+1; j<events.size()-1; j++) {
                float d2 = length(events[j].getWindowPos() - event.getWindowPos());
                float d3 = length(events[j].getWindowPos() - events[i].getWindowPos());
                
                if(abs(d2 - CARD_D2)<CARD_PRECISSION && abs(d3 - CARD_D1)<CARD_PRECISSION) {
                    std::cout << "A CARD WAS FOUND!" << std::endl;
                    
                    //One short and one long vector from events[i]
                    vec2 side1 = events[j].getWindowPos() - events[i].getWindowPos(); //short
                    vec2 side2 = event.getWindowPos()- events[i].getWindowPos(); //long
                    
                    //centerpoint is found by going in the directions of the edge vectors from event corner
                    vec2 centerpoint = event.getWindowPos() + 0.3f*side1 + 0.4f*side2;
                    
                    //if centerpoint matches that of the marker the touchpoints are the table legs
                    if(length(getPosition() - centerpoint) < CARD_PRECISSION) {
                        touchId.push_back(event.getId()); //first is sharp edge
                        touchId.push_back(events[j].getId());
                        touchId.push_back(events[i].getId());
                        return true;
                    }
                }
                else if(abs(d2 - CARD_D1)<CARD_PRECISSION && abs(d3 - CARD_D2)<CARD_PRECISSION) {
                    std::cout << "A CARD WAS FOUND!" << std::endl;
                    
                    //One short and one long vector from event
                    vec2 side1 = events[j].getWindowPos() - event.getWindowPos(); //short
                    vec2 side2 = events[i].getWindowPos() - event.getWindowPos(); //long
                    
                    //centerpoint is found by going in the directions of the edge vectors from event corner
                    vec2 centerpoint = event.getWindowPos() + 0.3f*side1 + 0.4f*side2;
                    
                    //if centerpoint matches that of the marker the touchpoints are the table legs
                    if(length(getPosition() - centerpoint) < CARD_PRECISSION) {
                        touchId.push_back(events[i].getId()); //first is sharp edge
                        touchId.push_back(event.getId());
                        touchId.push_back(events[j].getId());
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


float RealCard::constrain(float val, float min, float max) {
	if (val > max)
		return max;
	else if (val < min)
		return min;
	else
		return val;
}

ci::vec2 RealCard::attract(VirtualCardRef& c) {
	ci::vec2 force = ci::vec2(getPosition().x - c->getPosition().x, getPosition().y - c->getPosition().y);// Calculate direction of force
	float d = sqrt(force.x * force.x + force.y * force.y);				// Distance between objects
	d = constrain(d, 5.0, 25.0);										// Limiting the distance to eliminate "extreme" results for very close or very far objects
																		//ci::app::console() << d << std::endl;
	force = normalize(force);											// Normalize vector (distance doesn't matter here, we just want this vector for direction)
	float strength = (mass*c->mass*G) / (d * d);						// Calculate gravitional force magnitude
	force *= strength;													// Get force vector --> magnitude * direction
	return force;
}

void RealCard::update() {

	for (int i = 0; i < vCards.size(); i++) {


		ci::vec2 force = attract(vCards[i]);

		vCards[i]->applyForce(force);
		//ci::app::console() << getPosition() << std::endl;
		vCards[i]->setRcPos(getPosition());
		vCards[i]->update();
	}
}
