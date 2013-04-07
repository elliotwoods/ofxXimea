//
//  ofxXimea.cpp
//
//  Created by Elliot Woods on 04/04/2013.
//
//

#include "ofxXimea.h"

#ifndef __func__
#define __func__ __FUNCTION__
#endif
#define LOG_ERROR ofLogError("ofxMachineVision::" + string(__func__))
#define CHECK_FAIL(operation, result, return_instance) if (result != XI_OK) { LOG_ERROR << "Error during " << operation << " (" << result << ")"; return return_instance; }

namespace ofxXimea {
    
    //---------
    ofxMachineVision::Device::Specification Device::customOpen(int deviceID) {
        XI_RETURN status = XI_OK;
        
        status = xiOpenDevice(deviceID, &handle);
        CHECK_FAIL("open device", status, Specification());
        
        int sensorWidth, sensorHeight;
		
        status = xiGetParamInt(handle, XI_PRM_WIDTH, &sensorWidth);
        CHECK_FAIL("get sensor width", status, Specification());
        
        status = xiGetParamInt(handle, XI_PRM_HEIGHT, &sensorHeight);
        CHECK_FAIL("get sensor width", status, Specification());
        
        char deviceName[100];
        status = xiGetParamString(handle, XI_PRM_DEVICE_NAME, deviceName, 100);
        CHECK_FAIL("get device name", status, Specification());
        
        ofxMachineVision::Device::Specification specification(sensorWidth, sensorHeight, "Ximea", string(deviceName));

        specification.addFeature(ofxMachineVision::Device::Feature_FreeRun);
        specification.addFeature(ofxMachineVision::Device::Feature_OneShot);
        specification.addFeature(ofxMachineVision::Device::Feature_PixelClock);
        specification.addFeature(ofxMachineVision::Device::Feature_Triggering);
        specification.addFeature(ofxMachineVision::Device::Feature_Binning);
        specification.addFeature(ofxMachineVision::Device::Feature_Gain);
        specification.addFeature(ofxMachineVision::Device::Feature_Exposure);
        
        specification.addTriggerMode(ofxMachineVision::Device::Trigger_Device);
        specification.addTriggerMode(ofxMachineVision::Device::Trigger_GPIO1);
        specification.addTriggerMode(ofxMachineVision::Device::Trigger_Software);
        
        specification.addTriggerSignalType(ofxMachineVision::Device::TriggerSignal_Default);
        specification.addTriggerSignalType(ofxMachineVision::Device::TriggerSignal_RisingEdge);
        specification.addTriggerSignalType(ofxMachineVision::Device::TriggerSignal_FallingEdge);
        
		return specification;
    }
    
    //----------
    void Device::customClose() {
        xiCloseDevice(handle);
    }
    
    //----------
    bool Device::customStart(const TriggerMode & triggerMode, const TriggerSignalType & triggerSignalType) {
        XI_RETURN status = XI_OK;
        
        if (!setTriggerMode(triggerMode, triggerSignalType)) {
            LOG_ERROR << "Failed to start acquisition with desired trigger mode";
            return false;
        }
        
        status = xiStartAcquisition(handle);
        CHECK_FAIL("start acquisition", status, false);

		status = xiSetParamInt(handle, XI_PRM_EXPOSURE, 10000);
        CHECK_FAIL("set default exposure", status, false);

        return true;
    }
    
    //----------
    void Device::customStop() {
        XI_RETURN status = xiStopAcquisition(handle);
        CHECK_FAIL("stop acquisition", status, );
    }

    //----------
    bool Device::customPollFrame() {
        XI_RETURN status = xiGetImage(handle, 5000, &image);
        CHECK_FAIL("get image from camera", status, false);
		
		this->getPixelsRef().setFromExternalPixels((unsigned char *) image.bp, image.width, image.height, 1);

        return true;
    }
    
    //----------
    bool Device::setTriggerMode(const ofxMachineVision::Device::TriggerMode & triggerMode, const ofxMachineVision::Device::TriggerSignalType & triggerSignalType) {
        XI_RETURN status = XI_OK;
        switch (triggerMode) {
            case ofxMachineVision::Device::Trigger_Device:
                break;
            case ofxMachineVision::Device::Trigger_GPIO1:
                switch (triggerSignalType) {
                    case ofxMachineVision::Device::TriggerSignal_RisingEdge:
                        status = xiSetParamInt(handle, XI_PRM_TRG_SOURCE, XI_TRG_EDGE_RISING);
                        CHECK_FAIL("Set trigger to GPIO input rising edge", status, false);
                        break;
                    case ofxMachineVision::Device::TriggerSignal_FallingEdge:
                        status = xiSetParamInt(handle, XI_PRM_TRG_SOURCE, XI_TRG_EDGE_FALLING);
                        CHECK_FAIL("Set trigger to GPIO input falling edge", status, false);
                        break;
                    default:
                        break;
                }
                break;
            case ofxMachineVision::Device::Trigger_Software:
                status = xiSetParamInt(handle, XI_PRM_TRG_SOURCE, XI_TRG_SOFTWARE);;
                CHECK_FAIL("Set trigger to software", status, false);
                break;
            default:
                break;
        }
        return true;
    }
    
    
}
/*
 // structure containing information about trigger functionality
 typedef enum
 {
 XI_TRG_OFF                   =0, // Camera works in free run mode.
 XI_TRG_EDGE_RISING           =1, // External trigger (rising edge).
 XI_TRG_EDGE_FALLING          =2, // External trigger (falling edge).
 XI_TRG_SOFTWARE              =3, // Software(manual) trigger.
 XI_TRG_OUT                   =4, // Camera works in free run mode. Outputs sync sugnals.
 
 
#define HandleResult(res,place) if (res!=XI_OK) {printf("Error after %s (%d)",place,res);goto finish;}

int notmain(int argc, _TCHAR* argv[])
{
	// image buffer
	XI_IMG image;
	image.size = sizeof(XI_IMG);
	image.bp = NULL;
	image.bp_size = 0;
    
	// Sample for XIMEA API V2.10
	HANDLE xiH = NULL;
	XI_RETURN stat = XI_OK;
    
	// Get number of camera devices
	DWORD dwNumberOfDevices = 0;
	stat = xiGetNumberDevices(&dwNumberOfDevices);
	HandleResult(stat,"xiGetNumberDevices (no camera found)");
	
	if (!dwNumberOfDevices)
	{
		printf("No camera found\n");
		goto finish;
	}
	
	// Retrieving a handle to the camera device
	stat = xiOpenDevice(0, &xiH);
	HandleResult(stat,"xiOpenDevice");
	
	// Setting "exposure" parameter (10ms=10000us)
	stat = xiSetParamInt(xiH, XI_PRM_EXPOSURE, 10000);
	HandleResult(stat,"xiSetParam (exposure set)");
	
	xiStartAcquisition(xiH);
	HandleResult(stat,"xiStartAcquisition");
	
#define EXPECTED_IMAGES 100
	for (int images=0;images < EXPECTED_IMAGES;images++)
	{
        clock_t start = clock();
		// getting image from camera
		stat = xiGetImage(xiH, 5000, &image);
		HandleResult(stat,"xiGetImage");
		printf("Image %d (%dx%d) received from camera\n", images, (int)image.width, (int)image.height);
        float fps = 1.0f / (float(clock() - start) / float(CLOCKS_PER_SEC));
        printf("fps = %.2f\n", fps);
	}
    
finish:
	// Close device
	if (xiH)
		xiCloseDevice(xiH);
	printf("Done\n");
#ifdef WIN32
	Sleep(2000);
#endif
	return 0;
}

*/