//
// Created by Johan Eriksson on 2017-03-20.
//

#include "functions.h"
#include <iostream>

void functions::xml(const char *file, std::vector<CardHandler> &cards) {
    //TODO:: add checks if for example the path has spaces or other thing that we don't want
    tinyxml2::XMLDocument doc;
    doc.LoadFile(file);
    if (doc.ErrorID() != 0) {
        std::cout << "failed to open xml file" << std::endl;
    } else {
        std::cout << "Loaded XML" << std::endl;
        std::string path, header_se, text_se, header_en, text_en;
        std::vector<std::string> categories;
        float scale = 1.0f;
        for (tinyxml2::XMLElement *child = doc.FirstChildElement("content")->FirstChildElement("media");
             child != 0; child = child->NextSiblingElement()) {
            categories = {};
            if (child->Attribute("path")) {
                path = child->Attribute("path");
            }
            if (child->Attribute("scale_exp")) {
                scale = std::atof(child->Attribute("scale_exp"));
                //f(float) std::stod(child->Attribute("scale_exp"));
            }
            if (child->FirstChildElement("category")) {
                categories.push_back(child->FirstChildElement("category")->Attribute("name"));
                if (child->FirstChildElement("category")->NextSiblingElement("category")) {
                    for (tinyxml2::XMLElement *categ = child->FirstChildElement("category")->NextSiblingElement(
                            "category"); categ != 0; categ = categ->NextSiblingElement("category")) {
                        categories.push_back(categ->Attribute("name"));
                    }
                }
            }
            if (child->FirstChildElement("se")->FirstChildElement("header")->GetText()) {
                header_se = child->FirstChildElement("se")->FirstChildElement("header")->GetText();
            }
            if (child->FirstChildElement("se")->FirstChildElement("text")->GetText()) {
                text_se = child->FirstChildElement("se")->FirstChildElement("text")->GetText();
            }
            if (child->FirstChildElement("en")->FirstChildElement("header")->GetText()) {
                header_en = child->FirstChildElement("en")->FirstChildElement("header")->GetText();
            }
            if (child->FirstChildElement("en")->FirstChildElement("text")->GetText()) {
                text_en = child->FirstChildElement("en")->FirstChildElement("text")->GetText();
            }
            CardHandler someNewObject =  CardHandler(path, scale, categories, header_se, text_se, header_en, text_en);
            cards.push_back(someNewObject);
        }
    }
}

// displays the content in the predefined tags
void functions::displayxml(const char *file) {
    tinyxml2::XMLDocument doc;
    doc.LoadFile(file);
    if(doc.ErrorID() != 0 ){
        std::cout << "failed to open xml file" << std::endl;
    }
    else {
        std::cout << "Loaded XML" << std::endl;
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
