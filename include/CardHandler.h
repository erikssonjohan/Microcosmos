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

#ifndef SDL_TEST_CARDHANDLER_H
#define SDL_TEST_CARDHANDLER_H

class CardHandler {
public:
    /*!
     * a constructor of some sort that might not be used ? idk...
     */
    CardHandler();

    /*!
     *
     * A constructor for the CardHandler just based on the XML
     *
     * @param path - path to the media (image/film)
     * @param scale - scaling of the media
     * @param categories - the contents categories
     * @param header_se - the header/name of the content (se)
     * @param text_se - the text of the content (se)
     * @param header_en he header/name of the content (en)
     * @param text_en - the text of the content (en)
     */
    CardHandler(std::string path, float scale, std::vector<std::string> categories, std::string header_se,
                std::string text_se, std::string header_en, std::string text_en );

    virtual ~CardHandler();

    /*!
     * Prints the @p path, @p scale, @p categories, @p header_se, @p text_se, @p header_en and @p text_en in the console
     */
    void displayContent();

    /*!
     *
     */
    void eventHandler();

    /*!
     *
     */
    void mediaContent();

    /*!
     *
     */
    void textContent();

    /*!
     *
     */
    void rotation();


    /*!
     *
     * @return
     */
    int getPosX();

    /*!
     *
     * @return
     */
    int getPosY();

    /*!
     *
     * @param x
     * @param y
     */
    void changePos(int x, int y);

private:

    glm::vec3 position;
    virtualCard* vc;
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
