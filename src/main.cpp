
//include SDL
#include <string>
#include <iostream>
#include "SDL.h"
//include GLEW
#include "GL/glew.h"
#include "tinyxml2/tinyxml2.h"

// TODO::Put where it fits better
void xml(const char *file );

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;


int main(int argc, char* args[]) {


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
			SDL_Delay(10000);
		}
	}

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
	
}


// TODO::Put where it fits better
void xml(const char *file) {
    tinyxml2::XMLDocument doc;
    doc.LoadFile(file);
    if(doc.ErrorID() != 0 ){
        std::cout << "failed to open xml file" << std::endl;
    }
    else {
        std::cout << "Loaded XML" << std::endl;
        tinyxml2::XMLElement* mediaElement = doc.FirstChildElement( "media" );
        //const char* title = mediaElement->;
        //std::cout << "name: " << title << std::endl;
        for(tinyxml2::XMLElement* child = doc.FirstChildElement("content")->FirstChildElement("media");
            child != 0; child = child->NextSiblingElement())
        {
            if(child->Attribute("path")) {
                std::cout << "path = " << child->Attribute("path") << std::endl;
            }
            if(child->Attribute("scale_exp")) {
                std::cout << "scale_exp = " << child->Attribute("scale_exp") << std::endl;
            }
            if(child->FirstChildElement("category")) {
                std::cout << "category_name = " << child->FirstChildElement("category")->Attribute("name") << std::endl;
                if(child->FirstChildElement("category")->NextSiblingElement("category")){
                    for(tinyxml2::XMLElement* categ = child->FirstChildElement("category")->NextSiblingElement("category"); categ != 0; categ = categ->NextSiblingElement("category")) {
                        std::cout << "category_name = "
                                  << categ->Attribute("name")
                                  << std::endl;
                    }
                }
            }
            if(child->FirstChildElement("se")->FirstChildElement("header")->GetText()) {
                std::cout << "header_se = " << child->FirstChildElement("se")->FirstChildElement("header")->GetText()
                          << std::endl;
            }
            if(child->FirstChildElement("se")->FirstChildElement("text")->GetText()) {
                std::cout << "text_se = " << child->FirstChildElement("se")->FirstChildElement("text")->GetText()
                          << std::endl;
            }
            if(child->FirstChildElement("en")->FirstChildElement("header")->GetText()) {
                std::cout << "header_en = " << child->FirstChildElement("en")->FirstChildElement("header")->GetText()
                          << std::endl;
            }
            if(child->FirstChildElement("en")->FirstChildElement("text")->GetText()) {
                std::cout << "text_en = " << child->FirstChildElement("en")->FirstChildElement("text")->GetText()
                          << std::endl;
            }
            std::cout << std::endl;

        }



    }

}
