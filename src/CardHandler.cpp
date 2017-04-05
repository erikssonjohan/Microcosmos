//
// Created by Oscar Nord on 2017-03-08.
//

#include <vector>
#include "CardHandler.h"


//Simplest way to give new position, can be changed later
void CardHandler::changePos(float x,float y)
{
    position.x = x;
    position.y = y;
}

CardHandler::CardHandler(VirtualCard* virCard )
 : position(glm::vec3(0,0,0)), vc(virCard), scale(1.0f)
{

};






