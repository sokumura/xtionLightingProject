#include "testApp.h"
//////////////////
//////GLOBAL//////


//////////////////
//////////////////

//---
void EnumerateProductionTrees(ofxOpenNIContext _context, XnProductionNodeType type){
    xn::NodeInfoList nodes;
    _context.getXnContext().EnumerateProductionTrees(type, NULL, nodes);
    for (xn::NodeInfoList::Iterator it = nodes.Begin(); it != nodes.End(); ++it){
        std::cout << 
        ::xnProductionNodeTypeToString((*it).GetDescription().Type) <<
        ", " <<
        (*it).GetCreationInfo() << ", " <<
        (*it).GetInstanceName() << ", " <<
        (*it).GetDescription().strName << ", " <<
        (*it).GetDescription().strVendor << ", " << 
        std::endl;
        
        xn::NodeInfo info = *it;
        _context.getXnContext().CreateProductionTree(info);
    }
}
//--------------------------------------------------------------
void testApp::setup(){
	ofxFenster * win = ofxFensterManager::get()->createFenster(400 , 0, 1300, 900, OF_WINDOW);
	win -> addListener(new uiWindow());
	win -> setBackgroundColor(0,0,0);
    
    ui.setup();
//xtion--
    
	context.setupUsingXMLFile(ofToDataPath("openni/config/asus.xml", true));
    //context.setupUsingXMLFile(ofToDataPath("openni/config/SamplesConfig.xml", true));

    //EnumerateProductionTrees(context, XN_NODE_TYPE_DEVICE);
//    EnumerateProductionTrees(context, XN_NODE_TYPE_DEPTH);
//    xn::NodeInfoList nodeList;
//	context.getXnContext().EnumerateExistingNodes(nodeList);
//    
    
    depthGenerator.setup(&context);
//--xtion
}

//--------------------------------------------------------------
void testApp::update(){
	context.update();
	depthGenerator.update();
	
	//depthGeneratorから、深さとx,yの情報を得る
	//
	
}

//--------------------------------------------------------------
void testApp::draw(){
	depthGenerator.draw(0, 0, 640, 480);
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