//
// Created by Oscar Nord on 2017-03-08.
//

#include "../include/RenderSystem.h"
#include <stdio.h>



const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

RenderSystem::RenderSystem() {}

RenderSystem::~RenderSystem() {

}

void RenderSystem::renderer() {


}

void RenderSystem::texture() {

}

void RenderSystem::cardIdentifier() {

}

void RenderSystem::setRealCard() {

}

void RenderSystem::InitShader() {

}

void RenderSystem::init(){

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_GetError();
    } else {
        //Create window
        window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            SDL_GetError();
        }
        else
        {
            //Get window surface
            screenSurface = SDL_GetWindowSurface(window);

            //Fill the surface white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF00, 0xFF, 0xFF));

            SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            Renderer = renderer;

        }


    }



}


SDL_Renderer* RenderSystem::get_Renderer(){

    return Renderer;
}

SDL_Surface* RenderSystem::get_Surface(){



    return screenSurface;

}

SDL_Window* RenderSystem::get_Window(){



    return window;

}

void RenderSystem::destroy(){

    //Destroy window
    SDL_DestroyWindow(window);

    //Quit SDL subsystems
    SDL_Quit();

}