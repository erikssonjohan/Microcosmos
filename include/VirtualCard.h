//
// Created by Ola Rossing on 03/04/17.
//

#ifndef MIKROKOSMOS_VIRTUALCARD_H
#define MIKROKOSMOS_VIRTUALCARD_H
#include "SDL.h";
#include <string>
#include <iostream>
#include <vector>

class VirtualCard {
public:
    VirtualCard(std::string path, float scale, std::vector<std::string> categories, std::string header_se,
            std::string text_se, std::string header_en, std::string text_en );
    void displayContent();
private:
    std::string _path;
    float _scale;
    std::vector<std::string> _categories;
    std::string _header_se;
    std::string _text_se;
    std::string _header_en;
    std::string _text_en;
};


#endif //MIKROKOSMOS_VIRTUALCARD_H
