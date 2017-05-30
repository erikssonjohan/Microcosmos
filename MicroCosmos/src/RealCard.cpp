#include "RealCard.h"

RealCardRef RealCard::create(std::string category, int id, std::vector<VirtualCardRef> cards) {
    
    RealCardRef node(new RealCard()); //Using a default constructor for the moment
    //node->setup(category,id, cards); //Not neccessary to pass var category if member of RealCard
    return node;
}

void RealCard::setup(std::string category,int id,std::vector<VirtualCardRef> cards) {
    //creates virtualCards and save the refs to them in the vector virtualcards_
    virtualcards_ = cards;
    setName(category);
	category_ = category;
    id_ = id;

	circle_ = po::scene::Shape::createCircle(500);
	circle_->setFillColor(0, 1, 0, 1);
	circle_->setPosition(0,0);
	addChild(circle_);

    setV(false);
	setAlignment(po::scene::Alignment::CENTER_CENTER);

	getSignal(po::scene::TouchEvent::BEGAN_INSIDE).connect(std::bind(&RealCard::onTouchDown, this, std::placeholders::_1));
	getSignal(po::scene::TouchEvent::MOVED_INSIDE).connect(std::bind(&RealCard::onTouchDragged, this, std::placeholders::_1));
	getSignal(po::scene::TouchEvent::ENDED_INSIDE).connect(std::bind(&RealCard::onTouchUp, this, std::placeholders::_1));
	getSignal(po::scene::TouchEvent::ENDED).connect(std::bind(&RealCard::onTouchUp, this, std::placeholders::_1));
	
}


string RealCard::getCategory() {
	return category_;
}


void RealCard::setV(bool v){
    setVisible(v);
    for (int j = 0; j < virtualcards_.size(); ++j) {
        //std::cout  << virtualcards_.size() << getName() << " / " << virtualcards_[j]->getName() << std::endl;
        virtualcards_[j]->setVisible(v);
    }
}

void RealCard::initVcards(glm::vec2 rCardPos)
{

	//circle_->setPosition(rCardPos.x,rCardPos.y + 50);
	if (!realcard_initiated_)
	{
		int nrOfVirtcards = virtualcards_.size();
		const int radius = 200;

		//position the virtual cards around the real card and add as children
		for (int i = 0; i<nrOfVirtcards; ++i)
		{
			virtualcards_[i]->setPosition(ci::vec2(rCardPos.x + radius * cos(2 * M_PI * i / nrOfVirtcards), rCardPos.y + radius * sin(2 * M_PI * i / nrOfVirtcards)));
			getParent()->addChild(virtualcards_[i]);
			virtualcards_[i]->setName(getCategory() + "_" + virtualcards_[i]->getName());
		}
		realcard_initiated_ = true;
	}


}

void RealCard::resetInitiation()
{
	realcard_initiated_ = false;
}

int RealCard::getId() {
    return id_;
}

void RealCard::onTouchDown(po::scene::TouchEvent &event)
{
	ci::app::console() << "before PB";
	events_.push_back(event);
	ci::app::console() << "after PB";
}

//	Touch dragged event handler
void RealCard::onTouchDragged(po::scene::TouchEvent &event) {
	if (touchid_.empty())
		return;

	for (int i = 0; i<events_.size(); ++i) {
		if (leg_events_[i].getId() == event.getId()) {
			leg_events_[i] = event;
		}
	}

	// ** CENTERPOINT FUNCTION
	//two vectors 
	vec2 side1 = leg_events_[1].getWindowPos() - leg_events_[0].getWindowPos(); 
	vec2 side2 = leg_events_[2].getWindowPos() - leg_events_[0].getWindowPos(); 

	//simplified centerpoint
	vec2 centerpoint = leg_events_[0].getWindowPos() + 0.35f*side1 + 0.35f*side2;

	setPosition(centerpoint);
	ci::app::console() << "dragged";
	// **
}

void RealCard::onTouchUp(po::scene::TouchEvent &event) {
	ci::app::console() << "touch up" << std::endl;
	for(int i = 0; i<touchid_.size(); i++)
	if (event.getId() == touchid_[i])
	{
		touchid_.erase(touchid_.begin() + i);
	}
	removeTouchEvent(event);
}


//remove touchevent from events_
void RealCard::removeTouchEvent(po::scene::TouchEvent tEvent) {
	ci::app::console() << "remove touch events" << std::endl;
	for (int i = 0; i<events_.size(); ++i) {
		if (events_[i].getId() == tEvent.getId()) {
			events_.erase(events_.begin() + i);
		}
	}

	for (int i = 0; i < leg_events_.size(); ++i) {
		if (leg_events_[i].getId() == tEvent.getId()) {
			leg_events_.clear();
		}
	}
}

void RealCard::clearLegEvents() {
	leg_events_.clear();
}

//finds touchpoints and sets the RealCard position to the center
bool RealCard::findTouchpoints() {
	ci::app::console() << "size: " << events_.size() << std::endl;
	
	if (events_.empty())
	{
		//ci::app::console() << "TOM!";// << std::endl;
		return false;
	}
	else if (events_.size() < 3) {
		//ci::app::console() << "event<3" << std::endl;
		return false;
	}


	for (int i = 0; i < 3; i++) {
		leg_events_.push_back(events_[i]);
		touchid_.push_back(events_[i].getId());
		ci::app::console() << "id: " << events_[i].getId() << std::endl;
	}

	vec2 side1 = leg_events_[1].getWindowPos() - leg_events_[0].getWindowPos();
	vec2 side2 = leg_events_[2].getWindowPos() - leg_events_[0].getWindowPos();

	//simplified centerpoint
	vec2 centerpoint = leg_events_[0].getWindowPos() + 0.35f*side1 + 0.35f*side2;
	setPosition(centerpoint);
	ci::app::console() << "findTouch-setPosition" << std::endl;
	return true;
}

/*bool RealCard::findTouchpoints(){
	//ci::app::console() << "börjar söka tp" << std::endl;
	if (events_.empty())
	{
		//ci::app::console() << "TOM!";// << std::endl;
		return false;
	}
	else if (events_.size() < 3) {
		//ci::app::console() << "event<3" << std::endl;
		return false;
	}
	
	//The card has three points forminng a triangle with two different sidelengths
    float SCALE = 1.6; //To match values to screen koordinates
    float CARD_D1 = 56 * SCALE; //one shorter (56mm)
    float CARD_D2 = 66 * SCALE; //two longer (66mm)
    //float CARD_RADIUS = 36.5 * SCALE; //from card center to center of leg (36.5mm)
    float CARD_PRECISSION = 25* SCALE; //distances can differ

	//ci::app::console() << "hejsan" << std::endl;
    po::scene::TouchEvent event = events_.back();
	//ci::app::console() << "hej" << std::endl;
	//ci::app::console() << "size: " << events_.size() << std::endl;
    for(int i=0; i<events_.size()-1; i++) {
		
        float d1 = length(events_[i].getWindowPos() - event.getWindowPos());
		ci::app::console() << "d1 = " << d1 << std::endl;
        
        //test the rest of the touchpoints to find last point
        if(abs(d1 - CARD_D1) < CARD_PRECISSION) {
            //Shorter distance found -> both point should have longer length to third point
			ci::app::console() << "Found shorter distance!" << std::endl;
            for(int j=i+1; j<events_.size()-1; j++) {
                float d2 = length(events_[j].getWindowPos() - event.getWindowPos());
                float d3 = length(events_[j].getWindowPos() - events_[i].getWindowPos());
                
                if(abs(d2 - CARD_D2)<CARD_PRECISSION && abs(d3 - CARD_D2)<CARD_PRECISSION) {
					ci::app::console() << "A CARD WAS FOUND!" << std::endl;
                    
                    //One short and one long vector from event
                    vec2 side1 = events_[i].getWindowPos() - event.getWindowPos(); //short
                    vec2 side2 = events_[j].getWindowPos() - event.getWindowPos(); //long
                    
                    //centerpoint is found by going in the directions of the edge vectors from event corner
                    vec2 centerpoint = event.getWindowPos() + 0.3f*side1 + 0.4f*side2;

					// SET POSITION TO TRIANGLE CENTER
					setPosition(centerpoint);

                    //if centerpoint matches that of the marker the touchpoints are the table legs
                   // if(length(getPosition() - centerpoint) < CARD_PRECISSION) {
                        touchid_.push_back(events_[j].getId()); //first is sharp edge
                        touchid_.push_back(event.getId());
                        touchid_.push_back(events_[i].getId());
						
                        return true;
                   // }
                }
            }
        }
        
        else if(abs(d1 - CARD_D1) < CARD_PRECISSION) {
            //one longer distance found -> one short and one long left
			ci::app::console() << "Found one longer distance!" << endl;
            
            for(int j=i+1; j<events_.size()-1; j++) {
                float d2 = length(events_[j].getWindowPos() - event.getWindowPos());
                float d3 = length(events_[j].getWindowPos() - events_[i].getWindowPos());
                
                if(abs(d2 - CARD_D2)<CARD_PRECISSION && abs(d3 - CARD_D1)<CARD_PRECISSION) {
					ci::app::console() << "A CARD WAS FOUND!" << std::endl;
                    
                    //One short and one long vector from events_[i]
                    vec2 side1 = events_[j].getWindowPos() - events_[i].getWindowPos(); //short
                    vec2 side2 = event.getWindowPos()- events_[i].getWindowPos(); //long
                    
                    //centerpoint is found by going in the directions of the edge vectors from event corner
                    vec2 centerpoint = event.getWindowPos() + 0.3f*side1 + 0.4f*side2;
                    
                    //if centerpoint matches that of the marker the touchpoints are the table legs
                    if(length(getPosition() - centerpoint) < CARD_PRECISSION) {
                        touchid_.push_back(event.getId()); //first is sharp edge
                        touchid_.push_back(events_[j].getId());
                        touchid_.push_back(events_[i].getId());
                        return true;
                    }
                }
                else if(abs(d2 - CARD_D1)<CARD_PRECISSION && abs(d3 - CARD_D2)<CARD_PRECISSION) {
					ci::app::console() << "A CARD WAS FOUND!" << std::endl;
                    
                    //One short and one long vector from event
                    vec2 side1 = events_[j].getWindowPos() - event.getWindowPos(); //short
                    vec2 side2 = events_[i].getWindowPos() - event.getWindowPos(); //long
                    
                    //centerpoint is found by going in the directions of the edge vectors from event corner
                    vec2 centerpoint = event.getWindowPos() + 0.3f*side1 + 0.4f*side2;
                    
                    //if centerpoint matches that of the marker the touchpoints are the table legs
                    if(length(getPosition() - centerpoint) < CARD_PRECISSION) {
                        touchid_.push_back(events_[i].getId()); //first is sharp edge
                        touchid_.push_back(event.getId());
                        touchid_.push_back(events_[j].getId());
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

*/

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
	float strength = (mass_*c->mass*g_) / (d * d);						// Calculate gravitional force magnitude
	force *= strength;													// Get force vector --> magnitude * direction
	return force;
}

void RealCard::update() {

	for (int i = 0; i < virtualcards_.size(); i++) {


		ci::vec2 force_attract_ = attract(virtualcards_[i]);

		virtualcards_[i]->applyForce(force_attract_);
		//ci::app::console() << getPosition() << std::endl;
		virtualcards_[i]->setRcPos(getPosition());
		virtualcards_[i]->update();
	}
}
