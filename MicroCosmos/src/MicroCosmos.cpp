//
//  MicroCosmos.cpp
//  MicroCosmos
//
//  Created by Johan Eriksson on 2017-04-22.
//
//

#include "MicroCosmos.hpp"


using namespace po::scene;

MicroCosmosRef MicroCosmos::create(){
    MicroCosmosRef node (new MicroCosmos());
    node -> setup();
    return node;
}

void MicroCosmos::setup(){
    
    loadXML("demo.xml", cards);
    
    for (int i = 0; i<cards.size(); ++i) {
        cards[i]->setPosition(ci::vec2(cards[i]->x, cards[i]->y));
        addChild(cards[i]);
        std::cout << "add" << std::endl;
    }
    
    
    
}

void MicroCosmos::loadXML(const char *file, std::vector<VirtualCardRef> &cards)
{
    std::string path;
    std::vector<std::string> categories;
    std::string header_se;
    std::string text_se;
    std::string header_en;
    std::string text_en;
    //float scale;
    
    ci::XmlTree doc(  ci::app::loadAsset( file ) );
    for(  ci::XmlTree::Iter track = doc.begin("content/media"); track != doc.end(); ++track ){
        //console() << track->getAttribute("path").getValue() << endl;
        path = track->getAttribute("path").getValue();
        ci::app::console() << path << std::endl;
        ci::app::console() << track->getAttribute("scale_exp").getValue() << std::endl;
        //scale = std::atof(track->getAttribute("scale_exp").getValue());
        for( ci::XmlTree::Iter cat = track->begin("category"); cat != track->end(); ++cat ){
            //console() << cat->getAttribute("name").getValue() << endl;
            categories.push_back(cat->getAttribute("name").getValue());
            ci::app::console() << cat->getAttribute("name").getValue() << std::endl;
        }
        //console() << track->getChild("se/header").getValue() << endl;
        header_se = track->getChild("se/header").getValue();
        ci::app::console() << header_se << std::endl;
        //console() << track->getChild("se/text").getValue() << endl;
        text_se = track->getChild("se/text").getValue();
        ci::app::console() << text_se << std::endl;
        //console() << track->getChild("en/header").getValue() << endl;
        header_en = track->getChild("en/header").getValue();
        ci::app::console() << header_en << std::endl;
        //console() << track->getChild("en/text").getValue() << endl;
        text_en = track->getChild("en/text").getValue();
        ci::app::console() << text_en << std::endl;
        VirtualCardRef ref = VirtualCard::create(ci::Color(1,1,1),path, 1.0f, categories, header_se, text_se, header_en, text_en);
        cards.push_back(ref);
        ci::app::console() << std::endl;
    }
}
