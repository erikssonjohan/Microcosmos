#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cinder/Xml.h"
#include "VirtualCard.hpp"

using namespace ci;
using namespace ci::app;
using namespace std;

class MicroCosmosApp : public App {
  public:
    void setup() override;
    void mouseDown( MouseEvent event ) override;
    void touchesBegan( TouchEvent event ) override;
    void touchesMoved( TouchEvent event ) override;
    void touchesEnded( TouchEvent event ) override;
    void update() override;
    void draw() override;
    void loadXML(const char *file, std::vector<VirtualCard> &cards);
    std::vector<VirtualCard> cards;
};

void MicroCosmosApp::loadXML(const char *file, std::vector<VirtualCard> &cards)
{
    std::string path;
    std::vector<std::string> categories;
    std::string header_se;
    std::string text_se;
    std::string header_en;
    std::string text_en;
    //float scale;
    
    XmlTree doc(  loadAsset( file ) );
    for( XmlTree::Iter track = doc.begin("content/media"); track != doc.end(); ++track ){
        //console() << track->getAttribute("path").getValue() << endl;
        path = track->getAttribute("path").getValue();
        console() << path << endl;
        console() << track->getAttribute("scale_exp").getValue() << endl;
        //scale = std::atof(track->getAttribute("scale_exp").getValue());
        for( XmlTree::Iter cat = track->begin("category"); cat != track->end(); ++cat ){
            //console() << cat->getAttribute("name").getValue() << endl;
            categories.push_back(cat->getAttribute("name").getValue());
            console() << cat->getAttribute("name").getValue() << endl;
        }
        //console() << track->getChild("se/header").getValue() << endl;
        header_se = track->getChild("se/header").getValue();
        console() << header_se << endl;
        //console() << track->getChild("se/text").getValue() << endl;
        text_se = track->getChild("se/text").getValue();
        console() << text_se << endl;
        //console() << track->getChild("en/header").getValue() << endl;
        header_en = track->getChild("en/header").getValue();
        console() << header_en << endl;
        //console() << track->getChild("en/text").getValue() << endl;
        text_en = track->getChild("en/text").getValue();
        console() << text_en << endl;
        VirtualCard someNewObject =  VirtualCard(path, 1.0f, categories, header_se, text_se, header_en, text_en);
        cards.push_back(someNewObject);
        
        console() << endl;
    }
}

void prepareSettings( MicroCosmosApp::Settings *settings )
{
    // By default, multi-touch is disabled on desktop and enabled on mobile platforms.
    // You enable multi-touch from the SettingsFn that fires before the app is constructed.
    settings->setMultiTouchEnabled( true );
    
    // On mobile, if you disable multitouch then touch events will arrive via mouseDown(), mouseDrag(), etc.
    //	settings->setMultiTouchEnabled( false );
}

void MicroCosmosApp::setup()
{
    cinder::app::setFullScreen();
    
    loadXML("demo.xml", cards);
}


void MicroCosmosApp::mouseDown( MouseEvent event )
{
}

void MicroCosmosApp::touchesBegan( TouchEvent event )
{
    //CI_LOG_I( event );
    
    for( const auto &touch : event.getTouches() ) {
        for (int i = 0; i < cards.size(); ++i) {
            if(cards[i].isPointInShape(touch.getX(), touch.getY())){
                cards[i].touchId.push_back(touch.getId());
            }
        }
    }
}

void MicroCosmosApp::touchesMoved( TouchEvent event )
{
    //CI_LOG_I( event );
    for( const auto &touch : event.getTouches() ) {
        for (int i = 0; i < cards.size(); ++i) {
            if ( cards[i].touchIdInCard(touch.getId()) ) {
                cards[i].moveCard(touch.getPrevPos(), touch.getPos());
            }
        }
    }
}

void MicroCosmosApp::touchesEnded( TouchEvent event )
{
    //CI_LOG_I( event );
    for( const auto &touch : event.getTouches() ) {
        for (int i = 0; i < cards.size(); ++i) {
            if(cards[i].touchIdInCard(touch.getId())){
                cards[i].removeTouchId(touch.getId());
            }
        }
    }
}



void MicroCosmosApp::update()
{
}

void MicroCosmosApp::draw()
{
    gl::clear( Color( 0, 0, 0 ) );
    for (int i = 0; i<cards.size(); ++i) {
        //gl::pushModelMatrix();
        gl::pushMatrices();
        gl::translate(cards[i].trans);
        gl::rotate(cards[i].radAngle);
        
        
        cards[i].draw();
        //gl::popModelMatrix();
        gl::popMatrices();
    }
    
    // draw yellow circles at the active touch points
    gl::clearColor( Color( 1, 1, 0 ) );
    for( const auto &touch : getActiveTouches
        () ){
        gl::drawStrokedCircle( touch.getPos(), 20 );
    }
}

CINDER_APP( MicroCosmosApp, RendererGl, prepareSettings )
