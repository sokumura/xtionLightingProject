//
//  myDepthGenerator.h
//  xtionExample
//
//  Created by 奥村 周也 on 12/10/03.
//  Copyright 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef xtionExample_myDepthGenerator_h
#define xtionExample_myDepthGenerator_h

#include "XnCppWrapper.h"
#include "ofxOpenNI.h"
#include "ofMain.h"


typedef struct {
	int nearThreshold;
	int farThreshold;
} mydepth_threshold;

class myDepthGenerator {
	
public:
    std::vector<xn::DepthGenerator>	depth_generator;
    std::vector<ofTexture>	depth_texture;
    std::vector<unsigned char*>	depth_pixels;
    std::vector<unsigned char*>	mask_pixels;
    std::vector<mydepth_threshold> depth_thresholds;
    std::vector<int> max_depth;
    
    bool bUpdateMasks;
    //TODO: テクスチャーを作る（プレビュー）かどうかを受けて処理する記述を加える
    bool bGenerateTexture;
    int generatorNum;
	int	width, height;
    
    myDepthGenerator(){
        generatorNum = 0;
    }
	
    //----------------------------------------------
	bool setup(xn::NodeInfo& node){
        XnStatus result = XN_STATUS_OK;	
        xn::DepthGenerator dg;
        result = node.GetInstance(dg);
        if (result != XN_STATUS_OK) {
            ofLogError("myDepthGenerator.setup()", xnGetStatusString(result));
            return false;
        } else {
            depth_generator.push_back(dg);
            unsigned char maskp[640 * 480];
            mask_pixels.push_back(maskp);
           

            // make new map mode -> default to 640 x 480 @ 30fps
            XnMapOutputMode map_mode;
            map_mode.nXRes = XN_VGA_X_RES;
            map_mode.nYRes = XN_VGA_Y_RES;
            map_mode.nFPS  = 30;
            
            depth_generator[generatorNum].SetMapOutputMode(map_mode);
            
            // Default max depth is on GlobalDefaults.ini: MaxDepthValue=10000
            //ここ
            width		= map_mode.nXRes;
            height		= map_mode.nYRes;
            
            // TODO: add capability for b+w depth maps (more efficient for draw)
            ofTexture tex;
            tex.allocate(map_mode.nXRes, map_mode.nYRes, GL_RGBA);
            depth_texture.push_back(tex);
            depth_pixels.push_back(new unsigned char[map_mode.nXRes * map_mode.nYRes * 4]);
            memset(depth_pixels[generatorNum], 0, map_mode.nXRes * map_mode.nYRes * 4 * sizeof(unsigned char));
            
            // setup mask pixelskk
            int depthMax = depth_generator[generatorNum].GetDeviceMaxDepth();
            max_depth.push_back(depthMax);
            mask_pixels[generatorNum] = new unsigned char[width * height];
            mydepth_threshold thre;
            depth_thresholds.push_back(thre);
            depth_thresholds[generatorNum].nearThreshold = 0;
            depth_thresholds[generatorNum].farThreshold = max_depth[generatorNum - 1];
            
            printf("Depth camera No.%d inited\n", generatorNum);
            generatorNum++;
            bUpdateMasks = false;
            bGenerateTexture = true;//初期設定としては、プレビュー有り
            
            return true;
        }
    }
    //----------------------------------------------
    void startGeneratingAll(){
        for (int i = 0; i < generatorNum; i++){
            depth_generator[i].StartGenerating();
            printf("DepthGenerator%i Generating Start!\n", i);
        }
    }
	//----------------------------------------------
	void testDraw(float x=0, float y=0, float w=640, float h=480){
        glColor3f(1,1,1);
        for (int i = 0; i < generatorNum; i++) {
            depth_texture[i].draw(x + i * 660.0, y, w, h);
        }
    }
    //----------------------------------------------
	void update(){
        
        for (int i = 0; i < generatorNum; i++) {
            // get meta-data
            //depth_generator[0].WaitAndUpdateData();
            xn::DepthMetaData depthMD;
            depth_generator[i].GetMetaData(depthMD);
            //printf("depth_generator[%i]のデータをゲットしました。\n", i);
            if (bGenerateTexture) generateTexture(i, depthMD);
            if (bUpdateMasks) {
                updateMaskPixels(i, depthMD);
            }
        }

            
        
    }
    //----------------------------------------------
    void generateTexture(int textureNum, const xn::DepthMetaData& dmd){
        if (textureNum > generatorNum) {
            ofLogError("myDepthGenerator.generateTexture()", "不正なアクセス");
            return;
        }
        // get the pixels
        const XnDepthPixel* depth = dmd.Data();
        XN_ASSERT(depth);
        
        if (dmd.FrameID() == 0) return;
        
        // copy depth into texture-map
        float max;
        for (XnUInt16 y = dmd.YOffset(); y < dmd.YRes() + dmd.YOffset(); y++) {
            unsigned char * texture = (unsigned char*)depth_pixels[textureNum] + y * dmd.XRes() * 4 + dmd.XOffset() * 4;
            for (XnUInt16 x = 0; x < dmd.XRes(); x++, depth++, texture += 4) {
                XnUInt8 red = 0;
                XnUInt8 green = 0;
                XnUInt8 blue = 0;
                XnUInt8 alpha = 255;
                
                max = 255;	// half depth
                XnUInt8 a = (XnUInt8)(((*depth) / ( max_depth[textureNum] / max)));
                red		= a;
                green	= a;
                blue	= a;
                
                texture[0] = red;
                texture[1] = green;
                texture[2] = blue;
                
                if (*depth == 0)
                    texture[3] = 0;
                else
                    texture[3] = alpha;
            }
        }
        depth_texture[textureNum].loadData((unsigned char *)depth_pixels[textureNum], dmd.XRes(), dmd.YRes(), GL_RGBA);
        //printf("depth_texture[%i]を書き換えました。\n", textureNum);
    }
	//----------------------------------------------
    void setDepthThreshold(int forDepthThresholdNumber, int nearThreshold, int farThreshold){
        if (forDepthThresholdNumber > generatorNum) {
            ofLogError("myDepthGenerator.setDepthThreshold()", "不正なアクセス");
        } else {
            depth_thresholds[forDepthThresholdNumber].nearThreshold = nearThreshold;
            depth_thresholds[forDepthThresholdNumber].farThreshold = farThreshold;
        }
    }
	//----------------------------------------------
   void setThresholds(int thresholdsNumber, int nearThreshold, int farThreshold){
        if (thresholdsNumber > generatorNum) {
            ofLogError("myDepthGenerator.getDepthPixels()", "不正なアクセス");
        } else {
            depth_thresholds[thresholdsNumber].nearThreshold = nearThreshold;
            depth_thresholds[thresholdsNumber].farThreshold = farThreshold;
        }
 
    }
    //----------------------------------------------
    unsigned char*	getDepthPixels(int maskNumber){
        if (maskNumber > generatorNum) {
            ofLogError("myDepthGenerator.getDepthPixels()", "不正なアクセス");
        } else return mask_pixels[maskNumber];
    }

	//----------------------------------------------
    xn::DepthGenerator&	getXnDepthGenerator(int generatorNumber){
        if (generatorNumber > generatorNum) {
            ofLogError("myDepthGenerator.getXnDepthGenerator()", "不正なアクセス");
        } else
        return depth_generator[generatorNumber];
    }
    //----------------------------------------------
    void updateMaskPixels(int maskNumber, const xn::DepthMetaData& dmd){
        if (maskNumber > generatorNum) {
            ofLogError("myDepthGenerator.updateMaskPixels()", "不正なアクセス");
            return;
        }
        const XnDepthPixel* depth = dmd.Data();
        
        int numPixels = dmd.XRes() * dmd.YRes();
        
        for(int i = 0; i < numPixels; i++, depth++) {
            if(*depth < depth_thresholds[maskNumber].farThreshold && *depth > depth_thresholds[maskNumber].nearThreshold) {
                mask_pixels[maskNumber][i] = 255;
            } else {
                mask_pixels[maskNumber][i] = 0;
            }
            
        }
    }
    //-----------------------------------------------
	
	
};

#endif
