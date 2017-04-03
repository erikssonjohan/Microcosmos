//
// Created by Tobias on 2017-03-30.
//

#include "RealCard.h"

//called in init since we don't change any information in cards, pos is still unknown
RealCard::RealCard(std::string category, std::vector<CardHandler> &cards)
    : onTable(false), category(category), position(glm::vec3(0.0f ,0.0f, 0.0f))
{
    //Create vector of cardHandlers, one for each virtual card linked to the category
    //cardHandlers point to one virtual card each
    //..loop through cards and push back CH if cards.category contains category


    //set positions for cardHandlers relative to RealCard which depends on CH.size()
}

//card is placed on table -> give position, make visible
RealCard::Place(float x, float y)
{
    position.x = x;
    position.y = y;
    onTable = true;
}

