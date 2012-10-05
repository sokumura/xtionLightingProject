#include "testApp.h"
//////////////////
//////GLOBAL//////
const XnMapOutputMode OUT_PUT_MODE = { 640 , 480, 30 };

//////////////////
//////////////////

//--------------------------------------------------------------
void testApp::setup(){
	ofxFenster * win = ofxFensterManager::get()->createFenster(400 , 0, 1300, 900, OF_WINDOW);
	win -> addListener(new uiWindow());
	win -> setBackgroundColor(0,0,0);
    
    ui.setup();
//xtion--
    cout << "OpenNI ココカラ☆" << endl;
    depth_generator_num = 0;
    XnStatus nRetVal = XN_STATUS_OK;
    nRetVal = context.setup();
    if (nRetVal != XN_STATUS_OK) {
        logErrors(errors);
        ofLogError("OpenNI error : context.Init();", xnGetStatusString(nRetVal));
    }
    
    customEnumerateProductionTrees(context.getXnContext(), XN_NODE_TYPE_DEVICE);
    customEnumerateProductionTrees(context.getXnContext(), XN_NODE_TYPE_DEPTH);
    
    NodeInfoList nodeList;
    nRetVal = context.getXnContext().EnumerateExistingNodes(nodeList);
    if (nRetVal != XN_STATUS_OK) {
        ofLogError("OpenNI error : context.EnumerateExistingNodes();", xnGetStatusString(nRetVal));
        logErrors(errors);
    } else cout << "//////////////nodeExistings Successed!!!!///////////////" << endl;
    int geneNum = 0;
    for (NodeInfoList::Iterator it = nodeList.Begin(); it != nodeList.End(); ++it, geneNum++) {
        //インスタンス名の最後が番号になってるから、
        std::string name = (*it).GetInstanceName();
        cout << "--------------nodeInfomation------------\nname is : " << name << endl;
        int no = *name.rbegin() - '1';
        cout << "no is : " << no << endl;
        
        std::cout << 
        "GetCreationInfo() : " <<
        (*it).GetCreationInfo() << "\n" <<
        "GetInstanceName() : " <<
        (*it).GetInstanceName() << "\n" <<
        "GetDescription().strName : " <<
        (*it).GetDescription().strName << "\n" <<
        "GetDescription().strVendor : " <<
        (*it).GetDescription().strVendor << "\n" << 
        "-------/nodeInfomation-----" << std::endl;
        
        if ((*it).GetDescription().Type == XN_NODE_TYPE_DEPTH) {
            NodeInfo info = *it;
            bool result = depth_container.setup(info);
            if (!result) {
                logErrors(errors);
                ofLogError("OpenNI error: generatorSet : ", xnGetStatusString(nRetVal));
            }
            std::cout << "sensor[" << no << "]のdepthGeneratorを作成!!" << std::endl;
        }
        //logErrors(errors);
    }
    
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!\n%i 個のジェネレーターを作りました\n!!!!!!!!!!!!!!!!!!!!!!!!!!!\n", depth_container.generatorNum);
    //context.getXnContext().StartGeneratingAll();
    depth_container.startGeneratingAll();
    
//--xtion
}
/*--------------------------------------------------------------


 ------------*/
void testApp::logErrors(EnumerationErrors& rErrors){
    for(xn::EnumerationErrors::Iterator it = rErrors.Begin(); it != rErrors.End(); ++it) {
        XnChar desc[512];
		xnProductionNodeDescriptionToString(&it.Description(), desc,512);
		printf("%s failed: %s\n", desc, xnGetStatusString(it.Error()));
	}	
}
//-------------------------------
void testApp::customEnumerateProductionTrees(xn::Context& con, XnProductionNodeType type){
    NodeInfoList nodes;
    XnStatus rc = XN_STATUS_OK;
    rc = con.EnumerateProductionTrees(type, NULL, nodes);
    if (rc != XN_STATUS_OK) {
        ofLogError("MY TASK NO.1", xnGetStatusString(rc));
    } else if (nodes.Begin() == nodes.End()) {
        ofLogError("MY TASK NO.1", "No device found.");
    }
    
    for (NodeInfoList::Iterator it = nodes.Begin(); it != nodes.End(); ++it) {
        cout << "MY TASK NO.2 " <<
        xnProductionNodeTypeToString((*it).GetDescription().Type ) << ", " <<
        (*it).GetCreationInfo() << ", " <<
        (*it).GetInstanceName() << ", " <<
        (*it).GetDescription().strName << ", " <<
        (*it).GetDescription().strVendor << ", " << endl;
        
        NodeInfo info = *it;
        con.CreateProductionTree(info);
    }
    
}

//--------------------------------------------------------------
void testApp::update(){
	//xtion--
    context.getXnContext().WaitAndUpdateAll();
    for (int i = 0; i < depth_container.generatorNum; i++) {
        depth_container.update();
    }
	//--xtion
}

//--------------------------------------------------------------
void testApp::draw(){
    
    for (int i = 0; i < depth_container.generatorNum; i++) {
        depth_container.testDraw(0.0, 0.0, 640.0, 480.0);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if (key == ' ') {
        context.getXnContext().Release();
        cout << "RELEASED!!!" << endl;
    }
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