//
// Created by Ingela Rossing on 27/03/17.
//

#include "touchHandler.h"


void touchHandler::addFinger(SDL_TouchFingerEvent & tfe,std::vector<VirtualCard> &vc,  std::vector<RealCard>  &rc)
{
    //vec.push_back(tfe);
    v.push_back(TouchPoint(tfe));

    //NOTE: WE WILL NOT KNOW IF THE TFE IS A CARD EASILY!

    //if placed on virtual card
    if( 1 == 0) {
        // Add touchpoint to VirtualCard?
    }
    else if( 1 == 1 ) { //Belongs to real card
        // Show RealCard with updated position for card and virtual cards
        rc[0].place(tfe.x,tfe.y);
    }

    //std::cout << "Added id " << tfe.fingerId << std::endl;
    //std::cout << "Number of touch points on table: " << v.size() << std::endl;

}


void touchHandler::updateFinger(SDL_TouchFingerEvent &tfe, std::vector<RealCard>  &rc)
{
    //update in x,y,dx and dy in vector for tfe
    for(size_t i = 0; i < v.size(); i++)
    {
        if(tfe.fingerId == v[i].fingerId)
        {
            v[i].dx = tfe.dx;
            v[i].dy = tfe.dy;
            v[i].x = tfe.x;
            v[i].y = tfe.y;
            v[i].timestamp = tfe.timestamp;

            // std::cout << v[i].fingerId << " new (x,y) = (" << v[i].x << v[i].y << ")" << std::endl;
            return;
        }
    }
    // If not connected to real or virtual card: poll next event

    //If connected to virtual card:
    // check rotation, scaling and translation...
    //break;

    //If connected to real card:
    //move real card and its virtual cards

}


void touchHandler::removeFinger( SDL_FingerID fid, std::vector<RealCard>  &rc) {

    // If the finger is linked to a card: (inside touchHandler?)
    // remove touchpoint from virtual card?

    // or check if real card is removed (and remove real card)
    rc[0].pick_up();

    //remove from vector of touch points
    v.erase(
            std::remove_if(v.begin(), v.end(), [&](TouchPoint const & tp) {
                return tp.fingerId == fid;
            }),
            v.end());

    /* //if we use vector with tfe
    vec.erase(
            std::remove_if(vec.begin(), vec.end(), [&](SDL_TouchFingerEvent const & f) {
                return f.fingerId == fid;
            }),
            vec.end());
    */

    //std::cout << "Removed id " << fid << std::endl;
    //std::cout << "Number of touch points on table: " << v.size() << std::endl;
}
