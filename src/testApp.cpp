#include "testApp.h"
//////////////////
//////GLOBAL//////
bool shuyatest1 = false;
float myFloat1 = 0.56;
int myInt1 = 10;
int box1 = 3;
bool randomizeButton = true;
//////////////////
//////////////////

void uiWindow::setup(){
    
    gui.addTitle("Control Window");
    gui.addToggle("myBool1 Animate", shuyatest1);
    gui.addSlider("myFloat1: noise", myFloat1, 0.0, 1); 
    gui.addSlider("myInt1", myInt1, 100, 200); 
    gui.addComboBox("box1", box1, 12, NULL);
    gui.addButton("Randomize Background", randomizeButton);
    gui.show();
}
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
//--------------------------------------------------------------
void testApp::setup(){
	ofxFenster * win = ofxFensterManager::get()->createFenster(400 , 0, 1300, 900, OF_WINDOW);
	win -> addListener(new uiWindow());
	win -> setBackgroundColor(0,0,0);
    
    ui.setup();
//xtion--
    xtions.setup();
//--xtion
}

//--------------------------------------------------------------
void testApp::update(){
	//xtion--
    xtions.update();
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    //--xtion
}

//--------------------------------------------------------------
void testApp::draw(){
    xtions.draw();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}