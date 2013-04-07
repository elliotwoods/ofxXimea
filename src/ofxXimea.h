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
    class Device : public ofxMachineVision::Device {
    public:
    public:
        Device() : ofxMachineVision::Device(ofxMachineVision::Device::FreeRunMode_NeedsThread) { }
    protected:
        ofxMachineVision::Device::Specification customOpen(int deviceID);
        void customClose();
        bool customStart(const TriggerMode &, const TriggerSignalType &);
        void customStop();
        bool customPollFrame();
        
        bool setTriggerMode(const TriggerMode &, const TriggerSignalType &);
        
        HANDLE handle;
        XI_IMG image;
    };
}