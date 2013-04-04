//
//  ofxXimea.h
//
//  Created by Elliot Woods on 04/04/2013.
//
//

#pragma once
#include "ofxMachineVision.h"

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif

#ifdef __APPLE__
#include <m3api/xiApi.h>
#include <m3api/xiExt.h>
#else
#include "xiApi.h"
#include "xiExt.h"
#endif
#include <stdio.h>

#ifdef WIN32
// win32 only
#include <tchar.h>
#include <windows.h>
#include <conio.h>
#include <process.h>
#else
// linux
#define _tmain(a,b) main(a,b)
#define _TCHAR char
#define _getch()
#endif

namespace ofxXimea {
    class Device :: public ofxMachineVision::Device {
    public:
    protected:
        Device() : ofxMachineVision::Device(ofxMachineVision::Device::FreeRunMode_NeedsThread);
    protected:
        Specification customOpen(int deviceID);
        void customClose();
        bool customStart(TriggerMode);
        void customStop();
        bool customPollFrame();
        
        HANDLE handle;
    };
}