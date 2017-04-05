
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
#include "functions.h"
#include "touchHandler.h"
#include "RealCard.h"


// Global Variables
//SDL Window
SDL_Window* window = NULL;

//The surface contained by the window
SDL_Surface* screenSurface = NULL;


int main(int argc, char* args[]) {

    //TODO::here ?!
    //creats objects from xml and displays them... from->
    std::vector<VirtualCard> cards;
    functions::xml("write.xml", cards);

    std::vector<RealCard> realCards;

    touchHandler touchH;

    realCards.push_back(RealCard("virus", cards));

    //loop that creates a real card for all categories


    std::cout << cards.size() << std::endl;
    for (int i = 0; i < cards.size() ; ++i) {
        cards[i].displayContent();
        std::cout << std::endl;
    }
    //<-to

    RenderSystem renderSystem;
    renderSystem.init();
    bool running = true;
    SDL_Event event;


    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

                case SDL_QUIT: {
                    running = false;
                    break;
                }
                case SDL_FINGERDOWN: {
                    // Add finger to the vector of active touch points
                    // If the finger is a card it will be handled inside touchHandler
                    touchH.addFinger(event.tfinger,cards, realCards);
                    break;
                }
                case SDL_FINGERUP:{
                    // remove SDL_TouchFingerEvent with id fingerId and card if card
                    touchH.removeFinger(event.tfinger.fingerId, realCards);
                    break;
                }
                case SDL_FINGERMOTION:{
                    touchH.updateFinger(event.tfinger, realCards);
                    break;
                }
                default: break;
            }
        }
    }

   renderSystem.destroy();

    return 0;
}
