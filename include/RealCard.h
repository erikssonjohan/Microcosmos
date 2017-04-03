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

    RealCard(std::string category, std::vector<CardHandler>& cards);

private:
    glm::vec3 position;
    bool onTable;
    std::string category;
    std::vector<VirtualCard> VC;



};


#endif //MIKROKOSMOS_REALCARD_H
