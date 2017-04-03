//
// Created by Ingela Rossing on 03/04/17.
//

#ifndef MIKROKOSMOS_VIRTUALCARD_H
#define MIKROKOSMOS_VIRTUALCARD_H
#include "SDL.h";
#include <string>
#include <iostream>
#include <vector>

//Contains information inside card but no position since there can be doublets
class VirtualCard {
public:
    /*!
    *
    * A constructor for the VirtualCard just based on the XML
    *
    * @param path - path to the media (image/film)
    * @param scale - scaling of the media
    * @param categories - the contents categories
    * @param header_se - the header/name of the content (se)
    * @param text_se - the text of the content (se)
    * @param header_en he header/name of the content (en)
    * @param text_en - the text of the content (en)
    */
    VirtualCard(std::string path, float scale, std::vector<std::string> categories, std::string header_se,
            std::string text_se, std::string header_en, std::string text_en );

    /*!
    * Prints the @p path, @p scale, @p categories, @p header_se, @p text_se, @p header_en and @p text_en in the console
    */
    void displayContent();

    bool containsCategory(std::string c);

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
