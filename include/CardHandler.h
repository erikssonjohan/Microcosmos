//
// Created by Oscar Nord on 2017-03-08.
//


//include SDL
#include "SDL.h"
//include GLEW
#include "GL/glew.h"
//include glm
#include "glm/glm.hpp"
#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>
#include "VirtualCard.h"

#ifndef SDL_TEST_CARDHANDLER_H
#define SDL_TEST_CARDHANDLER_H


//
class CardHandler {
public:

    /*!
     * Constructor used in init
     */
    CardHandler(int x, int y, VirtualCard* virCard );

    /*!
     *
     * @return
     */
    int getPosX() {return position.x;};

    /*!
     *
     * @return
     */
    int getPosY() {return position.x;};

    /*!
     *
     * @param x
     * @param y
     */
    void changePos(int x, int y);

private:

    glm::vec3 position;
    VirtualCard* vc;
    float scale; //size of card
    //float angle; //not yet


    // VARIABLES WE DONT NEED?
    int card_width = 48; //same proportions for all cards -> only scale needed
    int card_height = 64;

    int origin_x, origin_y; //is position?
    int R,G,B; //not used anymore

    //moved to virtualCard class
    /*
    std::string _path;
    float _scale;
    std::vector<std::string> _categories;
    std::string _header_se;
    std::string _text_se;
    std::string _header_en;
    std::string _text_en;
     */
};


#endif //SDL_TEST_CARDHANDLER_H
