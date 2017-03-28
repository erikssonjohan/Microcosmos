//
// Created by Oscar Nord on 2017-03-08.
//

#include <vector>
#include "../include/CardHandler.h"
#include <stdio.h>



CardHandler::CardHandler() {}

CardHandler::~CardHandler() {}

CardHandler::CardHandler(std::string path, float scale, std::vector<std::string> categories, std::string header_se,
                         std::string text_se, std::string header_en, std::string text_en){
    _path = path;
    _scale = scale;
    _categories = categories;
    _header_se = header_se;
    _text_se = text_se;
    _header_en = header_en;
    _text_en = text_en;

}


CardHandler::CardHandler(int x, int y, int r, int g, int b) {

    R = r;
    G = g;
    B = b;

    rect.x = x;
    rect.y = y;
    rect.w = card_width;
    rect.h = card_height;
}


void CardHandler::displayContent(){

    std::cout << "path: " << _path << std::endl;
    std::cout << "scale: " << _scale << std::endl;
    std::cout << "categories: ";

    for (unsigned long i = 0; i < _categories.size(); ++i) {
        if(i == _categories.size()-1){
            std::cout << _categories[i] << std::endl;
        }
        else{
            std::cout << _categories[i] << ", ";
        }
    }

    std::cout << "header_se: " << _header_se << std::endl;
    std::cout << "text_se: " << _text_se << std::endl;
    std::cout << "header_en: " << _header_en << std::endl;
    std::cout << "text_en: " << _text_en << std::endl;

};



void CardHandler::eventHandler() {

}

void CardHandler::mediaContent() {

}

void CardHandler::textContent() {

}

void CardHandler::rotation() {

}

void CardHandler::render(SDL_Renderer* renderer) {

        SDL_SetRenderDrawColor(renderer,0,0,255,255);
        SDL_RenderClear(renderer);
}

void CardHandler::draw(SDL_Renderer* renderer){

    SDL_SetRenderDrawColor(renderer,R,G,B,255);
    SDL_RenderFillRect(renderer,&rect);
}


void CardHandler::changeColor(int r, int g, int b){

    SDL_FillRect(image, NULL, SDL_MapRGB(image->format, r, g, b));

}


int CardHandler::getPosX(){

    return rect.x;
}


int CardHandler::getPosY(){

    return rect.y;
}

void CardHandler::changePos(int x, int y){

    rect.x = rect.x + x;
    rect.y = rect.y + y;

}

SDL_Rect* CardHandler::getRect(){

    return &rect;

}





