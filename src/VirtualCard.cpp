//
// Created by Ingela Rossing on 03/04/17.
//

#include "VirtualCard.h"
VirtualCard::VirtualCard(std::string path, float scale, std::vector<std::string> categories, std::string header_se,
                         std::string text_se, std::string header_en, std::string text_en){
    _path = path;
    _scale = scale;
    _categories = categories;
    _header_se = header_se;
    _text_se = text_se;
    _header_en = header_en;
    _text_en = text_en;

}

void VirtualCard::displayContent(){

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