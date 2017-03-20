
#include <string>
#include <iostream>
#include <vector>

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



	//SDL Window
	SDL_Window* window = nullptr;

	//The surface contained by the window
	SDL_Surface* screenSurface = nullptr;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
        SDL_GetError();
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == nullptr)
		{
			SDL_GetError();
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);

			//Fill the surface white
			SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			//Update the surface
			SDL_UpdateWindowSurface(window);

			//Wait two seconds
			SDL_Delay(3000);
		}
	}

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
	
}