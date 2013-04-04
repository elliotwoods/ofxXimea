//
//  ofxXimea.cpp
//
//  Created by Elliot Woods on 04/04/2013.
//
//

#include "ofxXimea.h"

namespace ofxXimea {
    //-------
    Specification Device::customOpen(int deviceID) {
        XI_RETURN status = XI_OK;
        
        status = X
    }
}

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

