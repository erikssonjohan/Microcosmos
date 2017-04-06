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

    /*!
     *
     * called in init
     *
     * @param category
     * @param cards
     */
    RealCard(std::string category, std::vector<VirtualCard>& cards);



    /*!
     *
     * card is placed on table -> give position, make visible
     *
     * @param x
     * @param y
     */
    void place(float x, float y);

    /*!
     *
     */
    void pick_up() {onTable = false;};

    /*!
     *
     * Depending on method we might use dx and dy instead.
     *
     * @param newX
     * @param newY
     */
    void moveCard(float newX, float newY);



private:
    glm::vec3 position;             // Position of RealCard center point
    bool onTable;                   // Tells if we draw everything connected to this RealCard
    std::string category;           // Every RealCard has a category
    std::vector<CardHandler> CH;    // The cards surrounding the RealCard
                                    // Each of CardHandlers handles a virtual card connected to the category

    // If we have only one touch point on the card we can choose save the SDL_TouchId
};


#endif //MIKROKOSMOS_REALCARD_H
