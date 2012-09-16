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
	//context.setupUsingXMLFile(ofToDataPath("openni/config/asus.xml", true));
    XnStatus nRetVal = XN_STATUS_OK;
    nRetVal = context.setup();    
    NodeInfoList devicesList;
    int devicesListCount = 0;
    nRetVal = context.getXnContext().EnumerateProductionTrees(XN_NODE_TYPE_DEVICE, NULL, devicesList);
    for (NodeInfoList::Iterator it = devicesList.Begin(); it != devicesList.End(); ++it){
        devicesListCount++;
    }
    cout << "devicesListCount : " << devicesListCount << endl;
    
    int i=0;
    for (NodeInfoList::Iterator it = devicesList.Begin(); it != devicesList.End(); ++it, ++i){
        NodeInfo deviceInfo = *it;
        nRetVal = context.getXnContext().CreateProductionTree(deviceInfo, sensors[i].device);
        Query query;
        query.AddNeededNode(deviceInfo.GetInstanceName());
        nRetVal = context.getXnContext().CreateAnyProductionTree(XN_NODE_TYPE_DEPTH, &query, sensors[i].depth.getXnDepthGenerator());
    }
    context.getXnContext().StartGeneratingAll();
    
    
    
    //depthGenerator.setup(&context);
//--xtion
}

//--------------------------------------------------------------
void testApp::update(){
	context.update();
	//depthGenerator.update();
	for (int i = 0; i < NUM_OF_SENSORS; i++) {
        sensors[i].depth.update();
    }
	//depthGeneratorから、深さとx,yの情報を得る
	//
	
}

//--------------------------------------------------------------
void testApp::draw(){
    
	for (int i = 0; i < NUM_OF_SENSORS; i++){
        sensors[i].depth.draw(i*700, 0, 640, 480);
    }
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