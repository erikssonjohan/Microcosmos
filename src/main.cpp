/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and, strings
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <iostream>


//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Screen dimensions
SDL_Rect gScreenRect = { 0, 0, 320, 240 };


bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        SDL_Log( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            SDL_Log( "Warning: Linear texture filtering not enabled!" );
        }

        //Get device display mode
        SDL_DisplayMode displayMode;
        if( SDL_GetCurrentDisplayMode( 0, &displayMode ) == 0 )
        {
            gScreenRect.w = displayMode.w;
            gScreenRect.h = displayMode.h;
        }

        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gScreenRect.w, gScreenRect.h, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            SDL_Log( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                SDL_Log( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );


            }
        }
    }

    return success;
}


void close()
{
    //Free loaded images
    gPinchCloseTexture.free();
    gPinchOpenTexture.free();
    gRotateTexture.free();

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init() )
    {
        SDL_Log( "Failed to initialize!\n" );
    }
    else
    {

            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //Touch variables
            SDL_Point touchLocation = { gScreenRect.w / 2, gScreenRect.h / 2 };

            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                        //Window event
                    else if( e.type == SDL_WINDOWEVENT )
                    {
                        //Window resize/orientation change
                        if( e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED )
                        {
                            //Get screen dimensions
                            gScreenRect.w = e.window.data1;
                            gScreenRect.h = e.window.data2;

                            //Update screen
                            SDL_RenderPresent( gRenderer );
                        }
                    }
                        else if(e.type == SDL_FINGERDOWN){
                        std::cout << "(x,y): " << e.tfinger.x << ", " << e.tfinger.y << std::endl;

                    }


                        //Multi touch gesture
                    /*else if( e.type == SDL_MULTIGESTURE )
                    {
                        //Rotation detected
                        if( fabs( e.mgesture.dTheta ) > 3.14 / 180.0 )
                        {
                            touchLocation.x = e.mgesture.x * gScreenRect.w;
                            touchLocation.y = e.mgesture.y * gScreenRect.h;
                            std::cout << "rotate: " << e.mgesture.dTheta/180 << ". (x,y): " <<  touchLocation.x << ", " << touchLocation.y << std::endl;
                            //currentTexture = &gRotateTexture;
                        }
                            //Pinch detected
                        else if( fabs( e.mgesture.dDist ) > 0.002 )
                        {
                            touchLocation.x = e.mgesture.x * gScreenRect.w;
                            touchLocation.y = e.mgesture.y * gScreenRect.h;

                            //Pinch open
                            if( e.mgesture.dDist > 0 )
                            {
                              std::cout << "open:" <<   std::endl;
                              //  currentTexture = &gPinchOpenTexture;
                            }
                                //Pinch close
                            else
                            {
                                std::cout << "close" << std::endl;
                                //currentTexture = &gPinchCloseTexture;
                            }
                        }
                    }*/
                }

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                //Update screen
                SDL_RenderPresent( gRenderer );
            }

    }

    //Free resources and close SDL
    close();

    return 0;
}
