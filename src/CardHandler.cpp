//
// Created by Oscar Nord on 2017-03-08.
//

#include <vector>
#include "CardHandler.h"



void CardHandler::changePos(int x, int y){

}

CardHandler::CardHandler(int x, int y, VirtualCard* virCard )
 : position(glm::vec3(x,y,0)), vc(virCard), scale(0.0f)
{

};





