//
//  ofxXimea.h
//
//  Created by Elliot Woods on 04/04/2013.
//
//

#pragma once
#include "ofxMachineVision.h"

#include "m3api/xiApi.h"
#include "m3api/xiExt.h"

namespace ofxXimea {
	class Device : public ofxMachineVision::Device::Blocking {
    public:
		ofxMachineVision::Specification open(int deviceID = 0);
		void close();
		bool startCapture();
		void stopCapture();

		void setBinning(int binningX = 1, int binningY = 1);
		void setROI(const ofRectangle &);
		void setTriggerMode(const ofxMachineVision::TriggerMode &, const ofxMachineVision::TriggerSignalType &);
		
		void getFrame(ofxMachineVision::Frame &);
        
        HANDLE handle;
        XI_IMG image;
    };
}