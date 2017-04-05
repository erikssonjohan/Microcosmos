//
// Created by Tobias on 2017-03-30.
//

#include "RealCard.h"

//called in init since we don't change any information in cards, pos is still unknown
RealCard::RealCard(std::string category, std::vector<VirtualCard> &cards)
    : onTable(false), category(category), position(glm::vec3(0.0f ,0.0f, 0.0f))
{
    //Create vector of cardHandlers, one for each virtual card linked to the category
    //cardHandlers point to one virtual card each
    //..loop through cards and push back CH if cards.category contains category
    for(int i = 0; i<cards.size(); i++)
    {
        if(cards[i].containsCategory(category))
        {
            CardHandler ch(&cards[i]);
            CH.push_back(ch);
            std::cout << "added CardHandler" << std::endl;
        }
    }
    std::cout << "size of virus RealCard: " << CH.size() << std::endl;
    //set positions for cardHandlers relative to RealCard which depends on CH.size()
    for(int i = 0; i < CH.size(); i++)
        CH[i].changePos(50*cos(2*3.14*i/CH.size()), 50*sin(2*3.14*i/CH.size()));
}

//card is placed on table -> give position, make visible
void RealCard::place(float x, float y)
{
    position.x = x;
    position.y = y;
    onTable = true;
    //std::cout << "placed card" << std::endl;
}

void RealCard::moveCard(float newX, float newY)
{
    position.x = newX;
    position.y = newY;

    //If the virtual cards positions are relative to RealCard position they don't have to be updated :D
    //otherwise for all CH[i].changePos(newX,newY);
}

