//
// Created by Johan Eriksson on 2017-03-20.
//

#ifndef SDL_TEST_FUNCTIONS_H
#define SDL_TEST_FUNCTIONS_H

#include "CardHandler.h"
#include <string>
#include <iostream>
#include <vector>

//include tinyxml2
#include "tinyxml2/tinyxml2.h"
namespace functions {
    //CardHandler objects from file and puts it in the cards vector
    void xml(const char *file, std::vector<CardHandler> &cards);
    // displays the content in the predefined tags
    void displayxml(const char *file);



};


#endif //SDL_TEST_FUNCTIONS_H
