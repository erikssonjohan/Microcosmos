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
    CardHandler();

    CardHandler(std::string path, float scale, std::vector<std::string> categories, std::string header_se, std::string text_se, std::string header_en, std::string text_en );

    CardHandler(Uint32 color, int x, int y);

    virtual ~CardHandler();

    void displayContent();

    void eventHandler();

    void mediaContent();

    void textContent();

    void rotation();

    void render();

    void draw(SDL_Surface* destination,SDL_Window* window);

    void changeColor(int r, int g, int b);

    int getPosX();

    int getPosY();

    void changePos(int x, int y);

    SDL_Rect* getRect();

private:
    glm::vec3 position;
    int card_width = 48;
    int card_height = 64;
    SDL_Surface* image;
    SDL_Rect rect;
    int origin_x, origin_y;
    std::string _path;
    float _scale;
    std::vector<std::string> _categories;
    std::string _header_se;
    std::string _text_se;
    std::string _header_en;
    std::string _text_en;

};


#endif //SDL_TEST_CARDHANDLER_H
