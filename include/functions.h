//
// Created by Johan Eriksson on 2017-03-20.
//

#ifndef SDL_TEST_FUNCTIONS_H
#define SDL_TEST_FUNCTIONS_H

#include "VirtualCard.h"
#include <string>
#include <iostream>
#include <vector>

//include tinyxml2
#include "tinyxml2/tinyxml2.h"
namespace functions {
    /*!
     *
     * creates CardHandler objects from XML-file and puts it in the cards vector
     *
     * @param file - a XML-file (with the right structure)
     * @param cards - a vector of CardHandler where new CardHandlers can be created
     */
    void xml(const char *file, std::vector<VirtualCard> &cards);
    /*!
     *
     * Displays the content in the XML-file with the folowing tags:
     *
     * @param file - a XML-file (with the right structure)
     */
    void displayxml(const char *file);



};


#endif //SDL_TEST_FUNCTIONS_H
