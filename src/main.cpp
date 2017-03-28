
#include <string>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <RenderSystem.h>
#include <CardHandler.h>
#include <functions.h>
//include SDL
#include "SDL.h"
//include GLEW
#include "GL/glew.h"

//Include classes
#include "CardHandler.h"
#include "functions.h"
#include "touchHandler.h"


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

    RenderSystem renderSystem;
    renderSystem.init();
    bool running = true;
    SDL_Event event;
    int cards_size = 6;

    CardHandler obj1(20, 160,255,0,0);
    CardHandler obj2(160, 160,0,255,0);
    CardHandler obj3(260, 160,255,255,0);
    CardHandler obj4(340, 160,50,50,255);
    CardHandler obj5(480, 160,255,255,255);
    CardHandler obj6(620, 160,0,255,0);

    std::vector<CardHandler *> Cards;
    Cards.push_back(&obj1);
    Cards.push_back(&obj2);
    Cards.push_back(&obj3);
    Cards.push_back(&obj4);
    Cards.push_back(&obj5);
    Cards.push_back(&obj6);

    cards_size = 6;

    touchHandler touchH;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

                case SDL_QUIT: {
                    running = false;
                    break;
                }
                case (SDL_MOUSEMOTION): {
                    int x, y;
                    SDL_GetMouseState(&x, &y);

                    for (int i = 0; i < cards_size; i++) {
                        if (Cards[i]->getPosX() <= x && Cards[i]->getPosY() <= y && Cards[i]->getPosX() >= x - 48 &&
                            Cards[i]->getPosY() >= y - 64) {
                            Cards[i]->changePos(event.motion.xrel,event.motion.yrel);
                        }
                    }
                    break;
                }
                case SDL_FINGERDOWN: {
                    // Add finger to the vector of active touch points
                    // If the finger is a card it will be handled inside touchHandler
                    touchH.addFinger(event.tfinger);
                    break;
                }
                case SDL_FINGERUP:{
                    // remove SDL_TouchFingerEvent with id fingerId and card if card
                    touchH.removeFinger(event.tfinger.fingerId);
                    break;
                }
                case SDL_FINGERMOTION:{
                    touchH.updateFinger(event.tfinger);
                    break;
                }
                default: break;
            }

            for(int i = 0; i < cards_size;i++)
            {
                Cards[i]->render(renderSystem.get_Renderer());

                for(int x = 0;x<cards_size; x++)
                    Cards[x]->draw(renderSystem.get_Renderer());

                SDL_RenderPresent(renderSystem.get_Renderer());

            }
        }
    }

   renderSystem.destroy();

    return 0;
}
