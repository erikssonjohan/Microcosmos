#include "RealCard.h"

#include "poShape.h"


RealCardRef RealCard::create(std::string category) {
    
    RealCardRef node(new RealCard()); //Using a default constructor for the moment
    node->setup(category); //Not neccessary to pass var category if member of RealCard
    return node;
}

void RealCard::setup(std::string category)
{
    
    //creates virtualCards and save the refs to them in the vector vCards
    loadXML("demo.xml", vCards, category);
    int nrOfVirtcards = vCards.size();
    
    float radius = 300;
    
    //position the virtual cards around the real card and add as children
    for (int i = 0; i<nrOfVirtcards; ++i)
    {
        vCards[i]->setPosition(ci::vec2(radius * cos(6.28 * i/nrOfVirtcards), radius * sin(6.28 * i/nrOfVirtcards)));
        addChild(vCards[i]);
    }
    
    //std::cout << "nrOfVirtcards: " << nrOfVirtcards << std::endl;
    //std::cout << category << std::endl;
}

void RealCard::loadXML(const char *file, std::vector<VirtualCardRef> &cards, std::string category)
{
    std::string path;
    std::vector<std::string> categories;
    std::string header_se;
    std::string text_se;
    std::string header_en;
    std::string text_en;
    bool containsCategory = false;
    //float scale;
    
    ci::XmlTree doc(ci::app::loadAsset(file));
    for (ci::XmlTree::Iter track = doc.begin("content/media"); track != doc.end(); ++track) {
        //console() << track->getAttribute("path").getValue() << endl;
        path = track->getAttribute("path").getValue();
        ci::app::console() << path << std::endl;
        ci::app::console() << track->getAttribute("scale_exp").getValue() << std::endl;
        //scale = std::atof(track->getAttribute("scale_exp").getValue());
        for (ci::XmlTree::Iter cat = track->begin("category"); cat != track->end(); ++cat) {
            //console() << cat->getAttribute("name").getValue() << endl;
            if (!cat->getAttribute("name").getValue().compare(category))
                containsCategory = true;
            
            categories.push_back(cat->getAttribute("name").getValue());
            ci::app::console() << cat->getAttribute("name").getValue() << std::endl;
        }
        
        if (containsCategory)
        {
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
            VirtualCardRef ref = VirtualCard::create(ci::Color(1, 1, 1), path, 1.0f, categories, header_se, text_se, header_en, text_en);
            cards.push_back(ref);
            ci::app::console() << std::endl;
            containsCategory = false;
        }
        
    }
}