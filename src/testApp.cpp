#include "testApp.h"
//////////////////
//////GLOBAL//////

//////////////////
//////////////////

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