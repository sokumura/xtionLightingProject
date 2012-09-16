#pragma once

#include "ofMain.h"
#include "ofxFensterManager.h"
#include "ofxOpenCv.h"
#include "ofxOpenNI.h"
//#include "ofxSimpleGuiToo.h"

#define MAX_DEPTH 10000

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
    
	ofxOpenNIContext    context;
	ofxDepthGenerator   depthGenerator;
    
    uiWindow ui;
		
};
