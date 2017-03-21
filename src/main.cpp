
#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>

//include SDL
#include "SDL.h"
//include GLEW
#include "GL/glew.h"
//Include classes
#include "CardHandler.h"
#include "functions.h"


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


// Global Variables
//SDL Window
SDL_Window* window = NULL;

//The surface contained by the window
SDL_Surface* screenSurface = NULL;

void init();

int main(int argc, char* args[]) {


    //TODO::here ?!
    //creats objects from xml and displays them... from->
    /*std::vector<CardHandler> cards;
    functions::xml("write.xml", cards);
    std::cout << cards.size() << std::endl;
    for (int i = 0; i < cards.size() ; ++i) {
        cards[i].displayContent();
        std::cout << std::endl;
    }*/
    //<-to

    init();

    bool running = true;
    SDL_Event event;
    int cards_size = 6;


    Uint32 red = SDL_MapRGB(screenSurface->format, 255, 0, 0);
    Uint32 blue = SDL_MapRGB(screenSurface->format, 0, 0, 255);
    Uint32 green = SDL_MapRGB(screenSurface->format, 0, 255, 0);
    Uint32 cyan = SDL_MapRGB(screenSurface->format, 0, 255, 255);
    Uint32 magenta = SDL_MapRGB(screenSurface->format, 255, 0, 255);
    Uint32 yellow = SDL_MapRGB(screenSurface->format, 255, 255, 0);


    CardHandler obj1(red, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    CardHandler obj2(blue, SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2);
    CardHandler obj3(green, SCREEN_WIDTH / 8, SCREEN_HEIGHT / 2);
    CardHandler obj4(blue, SCREEN_WIDTH / 20, SCREEN_HEIGHT / 2);
    CardHandler obj5(magenta, SCREEN_WIDTH / 1.5, SCREEN_HEIGHT / 2);
    CardHandler obj6(yellow, SCREEN_WIDTH / 1.2, SCREEN_HEIGHT / 2);

    std::vector<CardHandler *> Cards;
    Cards.push_back(&obj1);
    Cards.push_back(&obj2);
    Cards.push_back(&obj3);
    Cards.push_back(&obj4);
    Cards.push_back(&obj5);
    Cards.push_back(&obj6);







    while (running) {


        while (SDL_PollEvent(&event)) {
            switch (event.type) {

                case (SDL_QUIT): {
                    running = false;
                    break;
                }

                case (SDL_MOUSEMOTION): {
                    int x, y;
                    SDL_GetMouseState(&x, &y);

                    for (int i = 0; i < cards_size; i++) {

                        if (Cards[i]->getPosX() <= x && Cards[i]->getPosY() <= y && Cards[i]->getPosX() >= x - 48 &&
                            Cards[i]->getPosY() >= y - 64) {
                            Cards[i]->changeColor(0, 250, 0);
                            Cards[i]->changePos(event.motion.xrel,event.motion.yrel);
                            //SDL_UpdateWindowSurface(window);
                        }

                    }


                }




            }

            for(int i = 0; i < cards_size;i++)
            {
                SDL_FillRect(screenSurface, NULL, blue);
                for(int x = 0;x<cards_size; x++)
                    SDL_FillRect(screenSurface,Cards[x]->getRect() , green);

                Cards[i]->draw(screenSurface,window);

            }


        }





    }







	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
	
}


void init() {


    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_GetError();
    } else {
        //Create window
        window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            SDL_GetError();
        } else {




                    //Get window surface
                    screenSurface = SDL_GetWindowSurface(window);

                    //Fill the surface white

                    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF00, 0xFF, 0xFF));




                    //Update the surface
                    SDL_UpdateWindowSurface(window);

                    //Wait two seconds

                    SDL_Delay(100);
                }
            }

        }





