//
// Created by Tobias on 2017-03-30.
//

#ifndef MIKROKOSMOS_REALCARD_H
#define MIKROKOSMOS_REALCARD_H

#include "glm/glm.hpp"
#include <vector>
#include <iostream>
#include "CardHandler.h"

class RealCard {
public:
    //called in init
    RealCard(std::string category, std::vector<CardHandler>& cards);

    //card is placed on table -> give position, make visible
    Place(float x, float y);


private:
    glm::vec3 position;
    bool onTable;
    std::string category;
    std::vector<CardHandler> CH;

};


#endif //MIKROKOSMOS_REALCARD_H
