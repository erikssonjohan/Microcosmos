//
// Created by Oscar Nord on 2017-03-08.
//
//include SDL
#include "SDL.h"
//include GLEW
#include "GL/glew.h"
//include glm
#include "glm/glm.hpp"


#ifndef SDL_TEST_RENDERSYSTEM_H
#define SDL_TEST_RENDERSYSTEM_H


class RenderSystem {
public:
    RenderSystem();

    virtual ~RenderSystem();

    void renderer();

    void texture();

    void cardIdentifier();

    void setRealCard();

    void InitShader();

    void init();

    SDL_Surface* get_Surface();

    SDL_Window* get_Window();

    SDL_Renderer* get_Renderer();

    void destroy();

private:
    int width;
    int height;
    SDL_Window* window = NULL;
    SDL_Surface* screenSurface = NULL;
    SDL_Renderer* Renderer = NULL;




};


#endif //SDL_TEST_RENDERSYSTEM_H
