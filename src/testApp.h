#pragma once

#include "ofMain.h"
#include "ofxFensterManager.h"
#include "ofxOpenCv.h"
#include "myDepthGenerator.h"
#include "ofxOpenNIHeaders.h"
#include "XnCppWrapper.h"

//#include "ofxSimpleGuiToo.h"

using namespace xn;

//#define MAX_DEPTH 10000

typedef vector<float> depth_hist;

class uiWindow : public ofxFensterListener {
public:
    void draw(){
//        gui.draw();
    }
    
private:
//    ofxSimpleGuiToo gui;
	
};


class testApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    depth_hist getDepthHistgram(const DepthGenerator& depth, const DepthMetaData& depthMD);
    void customEnumerateProductionTrees(xn::Context& context, XnProductionNodeType type);
    
    ofxOpenNIContext context;
    //DepthSensors sensors[NUM_OF_SENSORS];

    
    //fenster
    uiWindow ui;
    
    myDepthGenerator depth_container;
    int depth_generator_num;
    
private:
    EnumerationErrors errors;
    void logErrors(EnumerationErrors& rErrors);
		
};
