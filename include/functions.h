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

    /*!
     *
     * Get unique Categories in the xml file and put it in a vector of strings(Categories)
     *
     * @param file - a XML-file (with the right structure)
     * @param categorys - vector of unique categories
     */
    void uniqueCategories(const char *file, std::vector<std::string> &categories);

    /*!
     *
     * Checks if the category is in categories
     *
     * @param category - the category to check
     * @param categories - the vector
     * @return - returns true or false if category is in categories or not
     */
    bool stringInVector(std::string category, std::vector<std::string> categories);



};


#endif //SDL_TEST_FUNCTIONS_H
