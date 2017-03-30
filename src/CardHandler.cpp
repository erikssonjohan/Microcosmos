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

void CardHandler::changePos(int x, int y){

}





