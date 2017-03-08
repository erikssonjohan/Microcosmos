//
// Created by Oscar Nord on 2017-03-08.
//

//include SDL
#include "SDL.h"
//include GLEW
#include "GL/glew.h"
//include glm
#include "glm/glm.hpp"

#ifndef SDL_TEST_CARDHANDLER_H
#define SDL_TEST_CARDHANDLER_H


class CardHandler {
public:
    CardHandler();

    virtual ~CardHandler();

    void eventHandler();

    void mediaContent();

    void textContent();

    void rotation();

    void render();

private:
    glm::vec3 position;
    int card_width;
    int card_height;

};


#endif //SDL_TEST_CARDHANDLER_H
