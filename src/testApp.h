#pragma once

#include "ofMain.h"
#include "ofxFensterManager.h"
#include "ofxOpenCv.h"
#include "ofxOpenNI.h"
//#include "ofxSimpleGuiToo.h"

using namespace xn;

#define NUM_OF_SENSORS  2
#define MAX_DEPTH 10000

class uiWindow : public ofxFensterListener {
public:
    void draw(){
//        gui.draw();
    }
    
private:
//    ofxSimpleGuiToo gui;
	
};

struct DepthSensors {
    char name[80];
    ProductionNode device;
    ofxDepthGenerator depth;
    //DepthMetaData depthMD;
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
    
	ofxOpenNIContext    context;
	//ofxDepthGenerator   depthGenerator;
    DepthSensors sensors[NUM_OF_SENSORS];
    
    uiWindow ui;
		
};
