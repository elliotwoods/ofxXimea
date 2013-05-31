//
//  ofxXimea.cpp
//
//  Created by Elliot Woods on 04/04/2013.
//
//

#include "ofxXimea.h"

#define CHECK_FAIL(operation, result, return_instance) if (result != XI_OK) { OFXMV_ERROR << "Error [" << result << "] during " << operation << " (" << result << ")"; return return_instance; }

using namespace ofxMachineVision;

namespace ofxXimea {
    //---------
	Device::Device() {
		
	}

    //---------
    Specification Device::open(int deviceID) {
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

        Specification specification(sensorWidth, sensorHeight, "Ximea", string(deviceName));

        specification.addFeature(Feature_FreeRun);
        specification.addFeature(Feature_OneShot);
        specification.addFeature(Feature_PixelClock);
        specification.addFeature(Feature_Triggering);
		specification.addFeature(Feature_GPO);
		specification.addFeature(Feature_ROI);
        specification.addFeature(Feature_Gain);
        specification.addFeature(Feature_Exposure);
		
		specification.addPixelMode(Pixel_L8);
        
        specification.addTriggerMode(Trigger_Device);
        specification.addTriggerMode(Trigger_GPIO1);
        specification.addTriggerMode(Trigger_Software);
        
        specification.addTriggerSignalType(TriggerSignal_Default);
        specification.addTriggerSignalType(TriggerSignal_RisingEdge);
        specification.addTriggerSignalType(TriggerSignal_FallingEdge);
        
		specification.addGPOMode(GPOMode_On);
		specification.addGPOMode(GPOMode_Off);
		specification.addGPOMode(GPOMode_HighWhilstExposure);
		specification.addGPOMode(GPOMode_HighWhilstFrameActive);
		specification.addGPOMode(GPOMode_LowWhilstExposure);
		specification.addGPOMode(GPOMode_LowWhilstFrameActive);

		image.size = sizeof(XI_IMG);
		image.bp = NULL;
		image.bp_size = 0;

		this->lastTimestamp = 0;
		this->timestampOffset = 0;
		
		return specification;
    }
    
    //----------
	void Device::close() {
        xiCloseDevice(handle);
    }
    
    //----------
	bool Device::startCapture() {
        XI_RETURN status = XI_OK;
        
        status = xiStartAcquisition(handle);
        CHECK_FAIL("start acquisition", status, false);

		status = xiSetParamFloat(handle, XI_PRM_AEAG, 0);
		CHECK_FAIL("turn off auto exposure", status, false);

		return true;
    }
    
    //----------
	void Device::stopCapture() {
        XI_RETURN status = xiStopAcquisition(handle);
        CHECK_FAIL("stop acquisition", status, );
    }

    //----------
	void Device::setExposure(Microseconds exposure) {
		CHECK_FAIL("set exposure", xiSetParamInt(handle, XI_PRM_EXPOSURE, exposure), );
	}

    //----------
	void Device::setBinning(int binningX, int binningY) {
		if (binningX != binningY) {
			OFXMV_ERROR << "ofxXimea's api does not allow asymmetrical binning (" << binningX << "," << binningY << ")";
			binningY = binningX;
			OFXMV_ERROR << "Setting binning to (" << binningX << "," << binningY << ")";
		}

		if (!(binningX == 1 || binningX == 2 || binningX == 4)) {
			OFXMV_ERROR << "ofxXimea's api does not allow binning rates other than {1,2,4}";
			return;
		}

		XI_RETURN status;

		//we hard set to skipping here, as we presume you can do interpolation in your own code
		//and only skipping improves frame rate on ximea api.
		status = xiSetParamInt(handle, XI_PRM_DOWNSAMPLING_TYPE, XI_SKIPPING);
		CHECK_FAIL("set binning type", status, );

		status = xiSetParamInt(handle, XI_PRM_DOWNSAMPLING, binningX);
		CHECK_FAIL("set binning resolution", status, );
	}

    //----------
	void Device::setROI(const ofRectangle & roi) {
		XI_RETURN status;

		status = xiSetParamInt(handle, XI_PRM_WIDTH, (int) roi.width);
		CHECK_FAIL("set ROI width", status, );

		status = xiSetParamInt(handle, XI_PRM_HEIGHT, (int) roi.height);
		CHECK_FAIL("set ROI height", status, );

		status = xiSetParamInt(handle, XI_PRM_OFFSET_X, (int) roi.x);
		CHECK_FAIL("set ROI x", status, );

		status = xiSetParamInt(handle, XI_PRM_OFFSET_Y, (int) roi.y);
		CHECK_FAIL("set ROI y", status, );
	}
    
    //----------
    void Device::setTriggerMode(const TriggerMode & triggerMode, const TriggerSignalType & triggerSignalType) {
        XI_RETURN status = XI_OK;

        switch (triggerMode) {
            case Trigger_Device:
                break;
            case Trigger_GPIO1:

				status = xiSetParamInt(this->handle, XI_PRM_GPI_SELECTOR, 1);
				CHECK_FAIL("Set GPI port to 1", status, );

				status = xiSetParamInt(this->handle, XI_PRM_GPI_MODE, XI_GPI_TRIGGER);
				CHECK_FAIL("Set GPI port as input trigger", status, );

                switch (triggerSignalType) {
                    case TriggerSignal_RisingEdge:
                        status = xiSetParamInt(handle, XI_PRM_TRG_SOURCE, XI_TRG_EDGE_RISING);
                        CHECK_FAIL("Set trigger to GPIO input rising edge", status, );
                        break;
                    case TriggerSignal_FallingEdge:
                        status = xiSetParamInt(handle, XI_PRM_TRG_SOURCE, XI_TRG_EDGE_FALLING);
                        CHECK_FAIL("Set trigger to GPIO input falling edge", status, );
                        break;
                    default:
                        break;
                }
                break;
            case Trigger_Software:
                status = xiSetParamInt(handle, XI_PRM_TRG_SOURCE, XI_TRG_SOFTWARE);;
                CHECK_FAIL("Set trigger to software", status, );
                break;
            default:
                break;
        }
    }
    
	//----------
	void Device::setGPOMode(const GPOMode & gpoMode) {
        XI_RETURN status = XI_OK;

		status = xiSetParamInt(handle, XI_PRM_GPO_SELECTOR, 1);
		CHECK_FAIL("Turn GPO on for port 0", status, );
		
		int xiParam = -1;

		switch(gpoMode) {
		case GPOMode_On:
			xiParam = XI_GPO_ON;
			break;
		case GPOMode_Off:
			xiParam = XI_GPO_OFF;
			break;
		case GPOMode_HighWhilstExposure:
			xiParam = XI_GPO_EXPOSURE_ACTIVE;
			break;
		case GPOMode_HighWhilstFrameActive:
			xiParam = XI_GPO_FRAME_ACTIVE;
			break;
		case GPOMode_LowWhilstExposure:
			xiParam = XI_GPO_EXPOSURE_ACTIVE_NEG;
			break;
		case GPOMode_LowWhilstFrameActive:
			xiParam = XI_GPO_FRAME_ACTIVE_NEG;
			break;
		}

		status = xiSetParamInt(handle, XI_PRM_GPO_MODE, xiParam);
		CHECK_FAIL("Set GPO mode", status, );
	}

	//----------
	void Device::getFrame(Frame & frame) {
        XI_RETURN status = xiGetImage(handle, 5, &image);
		if (status != XI_OK) {
			if (status == XI_TIMEOUT) {
				//we might need a better mechanism for marking no returned frame
				// as this state might be propagated down to places that we don't want
				frame.setEmpty(true);
				return;
			} else {
				OFXMV_ERROR << "xiGetImage failed" << status;
				frame.setEmpty(true);
				return;
			}
		} else {
			ofPixels & pixels(frame.getPixelsRef());

			if (image.height != pixels.getHeight() || image.width != pixels.getWidth()) {
				pixels.allocate(image.width, image.height, OF_PIXELS_MONO);
			}

			pixels.setFromPixels( (unsigned char * ) image.bp, image.width, image.height, 1);

			// a pretty hacky way to unwravel looping timestamps into sequential timestamps
			Microseconds timestamp = image.tsUSec + timestampOffset;
			if (timestamp < lastTimestamp) {
				timestampOffset += 1e6;
				timestamp += 1e6;
			}

			frame.setTimestamp(timestamp);
			frame.setFrameIndex(image.nframe);
			frame.setEmpty(false);

			lastTimestamp = timestamp;
		}
	}
}