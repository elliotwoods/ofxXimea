
			
//-------------------------------------------------------------------------------------------------------------------
// xiApi header file
#ifndef __XIAPI_H
#define __XIAPI_H

#ifdef WIN32
#include <windows.h>
#else
// linux
#include "wintypedefs.h"
#endif

#ifdef XIAPI_EXPORTS
#define XIAPI __declspec(dllexport)
#else
#define XIAPI __declspec(dllimport)
#endif

typedef int XI_RETURN;

#ifdef __cplusplus
extern "C" {
#endif

//-------------------------------------------------------------------------------------------------------------------
// xiApi parameters

// 
#define  XI_PRM_DEVICE_NAME           "device_name"             // Return device name
#define  XI_PRM_DEVICE_TYPE           "device_type"             // Return device type
#define  XI_PRM_DEVICE_SN             "device_sn"               // Return device serian number
// 
#define  XI_PRM_EXPOSURE              "exposure"                // Exposure time in microseconds,
#define  XI_PRM_GAIN                  "gain"                    // Gain in dB,
#define  XI_PRM_DOWNSAMPLING          "downsampling"            // Change image resolution by binning or skipping.
#define  XI_PRM_DOWNSAMPLING_TYPE     "downsampling_type"       // Change image downsampling type.
#define  XI_PRM_IMAGE_DATA_FORMAT     "imgdataformat"           // Output data format.
#define  XI_PRM_FRAMERATE             "framerate"               // Define framerate
#define  XI_PRM_AVAILABLE_BANDWIDTH   "available_bandwidth"     // Calculate and return available interface bandwidth(int Megabits)
#define  XI_PRM_LIMIT_BANDWIDTH       "limit_bandwidth"         // Set/get bandwidth(datarate)(in Megabits)
#define  XI_PRM_BUFFER_POLICY         "buffer_policy"           // Data move policy
#define  XI_PRM_OFFSET_X              "offsetX"                 // Horizontal offset from the origin to the area of interest (in pixels).
#define  XI_PRM_OFFSET_Y              "offsetY"                 // Vertical offset from the origin to the area of interest (in pixels).
#define  XI_PRM_WIDTH                 "width"                   // Width of the Image provided by the device (in pixels).
#define  XI_PRM_HEIGHT                "height"                  // Height of the Image provided by the device (in pixels).
#define  XI_PRM_LUT_EN                "LUTEnable"               // Activates LUT.
#define  XI_PRM_LUT_INDEX             "LUTIndex"                // Control the index (offset) of the coefficient to access in the LUT.
#define  XI_PRM_LUT_VALUE             "LUTValue"                // Value at entry LUTIndex of the LUT
#define  XI_PRM_TRG_SOURCE            "trigger_source"          // Defines source of trigger.
#define  XI_PRM_TRG_SOFTWARE          "trigger_software"        // Generates an internal trigger. XI_PRM_TRG_SOURCE must be set to TRG_SOFTWARE.
#define  XI_PRM_GPI_SELECTOR          "gpi_selector"            // Selects GPI
#define  XI_PRM_GPI_MODE              "gpi_mode"                // Defines GPI functionality
#define  XI_PRM_GPI_LEVEL             "gpi_level"               // GPI level
#define  XI_PRM_GPO_SELECTOR          "gpo_selector"            // Selects GPO
#define  XI_PRM_GPO_MODE              "gpo_mode"                // Defines GPO functionality
#define  XI_PRM_LED_SELECTOR          "led_selector"            // Selects LED
#define  XI_PRM_LED_MODE              "led_mode"                // Defines LED functionality
// 
#define  XI_PRM_IS_DEVICE_EXIST       "isexist"                 // Returns 1 if camera connected and works properly.
#define  XI_PRM_ACQ_BUFFER_SIZE       "acq_buffer_size"         // Acquisition buffer size in bytes
#define  XI_PRM_BUFFERS_QUEUE_SIZE    "buffers_queue_size"      // Queue of field/frame buffers
#define  XI_PRM_RECENT_FRAME          "recent_frame"            // GetImage returns most recent frame
// 
#define  XI_PRM_CMS                   "cms"                     // Initialize/uninitialize CMS, perceptual inetent.
#define  XI_PRM_APPLY_CMS             "apply_cms"               // Apply CMS profiles(input.icc and output.icm), perceptual inetent.
#define  XI_PRM_INPUT_CMS_PROFILE     "input_cms_profile"       // Apply input CMS profile.
#define  XI_PRM_OUTPUT_CMS_PROFILE    "output_cms_profile"      // Apply output CMS profile.
#define  XI_PRM_IMAGE_IS_COLOR        "iscolor"                 // Returns 1 for color cameras.
#define  XI_PRM_COLOR_FILTER_ARRAY    "cfa"                     // Returns color filter array type of RAW data.
#define  XI_PRM_WB_KR                 "wb_kr"                   // White balance red coefficient
#define  XI_PRM_WB_KG                 "wb_kg"                   // White balance green coefficient
#define  XI_PRM_WB_KB                 "wb_kb"                   // White balance blue coefficient
#define  XI_PRM_MANUAL_WB             "manual_wb"               // Calculates White Balance(xiGetImage function must be called)
#define  XI_PRM_AUTO_WB               "auto_wb"                 // Automatic white balance
#define  XI_PRM_GAMMAY                "gammaY"                  // Luminosity gamma
#define  XI_PRM_GAMMAC                "gammaC"                  // Chromaticity gamma
#define  XI_PRM_SHARPNESS             "sharpness"               // Sharpness Strenght
#define  XI_PRM_CC_MATRIX_00          "ccMTX00"                 // Color Correction Matrix element [0][0]
#define  XI_PRM_CC_MATRIX_01          "ccMTX01"                 // Color Correction Matrix element [0][1]
#define  XI_PRM_CC_MATRIX_02          "ccMTX02"                 // Color Correction Matrix element [0][2]
#define  XI_PRM_CC_MATRIX_03          "ccMTX03"                 // Color Correction Matrix element [0][3]
#define  XI_PRM_CC_MATRIX_10          "ccMTX10"                 // Color Correction Matrix element [1][0]
#define  XI_PRM_CC_MATRIX_11          "ccMTX11"                 // Color Correction Matrix element [1][1]
#define  XI_PRM_CC_MATRIX_12          "ccMTX12"                 // Color Correction Matrix element [1][2]
#define  XI_PRM_CC_MATRIX_13          "ccMTX13"                 // Color Correction Matrix element [1][3]
#define  XI_PRM_CC_MATRIX_20          "ccMTX20"                 // Color Correction Matrix element [2][0]
#define  XI_PRM_CC_MATRIX_21          "ccMTX21"                 // Color Correction Matrix element [2][1]
#define  XI_PRM_CC_MATRIX_22          "ccMTX22"                 // Color Correction Matrix element [2][2]
#define  XI_PRM_CC_MATRIX_23          "ccMTX23"                 // Color Correction Matrix element [2][3]
#define  XI_PRM_CC_MATRIX_30          "ccMTX30"                 // Color Correction Matrix element [3][0]
#define  XI_PRM_CC_MATRIX_31          "ccMTX31"                 // Color Correction Matrix element [3][1]
#define  XI_PRM_CC_MATRIX_32          "ccMTX32"                 // Color Correction Matrix element [3][2]
#define  XI_PRM_CC_MATRIX_33          "ccMTX33"                 // Color Correction Matrix element [3][3]
#define  XI_SET_DEFAULT_CC_MATRIX     "defccMTX"                // Set default Color Correction Matrix
// 
#define  XI_PRM_AEAG                  "aeag"                    // Automatic exposure/gain
#define  XI_PRM_EXP_PRIORITY          "exp_priority"            // Exposure priority (0.5 - exposure 50%, gain 50%).
#define  XI_PRM_AE_MAX_LIMIT          "ae_max_limit"            // Maximum limit of exposure in AEAG procedure
#define  XI_PRM_AG_MAX_LIMIT          "ag_max_limit"            // Maximum limit of gain in AEAG procedure
#define  XI_PRM_AEAG_LEVEL            "aeag_level"              // Average intensity of output signal AEAG should achieve(in %)
// 
#define  XI_PRM_BPC                   "bpc"                     // Correction of bad pixels
// 
#define  XI_PRM_DEBOUNCE_EN           "dbnc_en"                 // Enable/Disable debounce to selected GPI
#define  XI_PRM_DEBOUNCE_T0           "dbnc_t0"                 // Debounce time (x * 10us)
#define  XI_PRM_DEBOUNCE_T1           "dbnc_t1"                 // Debounce time (x * 10us)
#define  XI_PRM_DEBOUNCE_POL          "dbnc_pol"                // Debounce polarity (pol = 1 t0 - falling edge, t1 - rising edge)
// 
#define  XI_PRM_IS_COOLED             "iscooled"                // Returns 1 for cameras that support cooling.
#define  XI_PRM_COOLING               "cooling"                 // Start camera cooling.
#define  XI_PRM_TARGET_TEMP           "target_temp"             // Set sensor target temperature for cooling.
#define  XI_PRM_CHIP_TEMP             "chip_temp"               // Camera chip temperature
#define  XI_PRM_HOUS_TEMP             "hous_temp"               // Camera housing tepmerature
// 
#define  XI_PRM_HDR                   "hdr"                     // Enable High Dynamic Range feature.
#define  XI_PRM_HDR_T1                "hdr_t1"                  // Exposure time of first slope(in microseconds)
#define  XI_PRM_HDR_T2                "hdr_t2"                  // Exposure time of second slope(in microseconds)
#define  XI_PRM_HDR_T3                "hdr_t3"                  // Exposure time of third slope(in microseconds)
#define  XI_PRM_KNEEPOINT1            "hdr_kneepoint1"          // First kneepoint (% of sensor saturation)
#define  XI_PRM_KNEEPOINT2            "hdr_kneepoint2"          // Second kneepoint (% of sensor saturation)
// 
#define  XI_PRM_API_VERSION           "api_version"             // Returns version of API.
#define  XI_PRM_DRV_VERSION           "drv_version"             // Returns version of current device driver.

//-------------------------------------------------------------------------------------------------------------------
// Error codes xiApi
typedef enum
{	
	XI_OK                             = 0, // Function call succeeded
	XI_INVALID_HANDLE                 = 1, // Invalid handle
	XI_READREG                        = 2, // Register read error
	XI_WRITEREG                       = 3, // Register write error
	XI_FREE_RESOURCES                 = 4, // Freeing resiurces error
	XI_FREE_CHANNEL                   = 5, // Freeing channel error
	XI_FREE_BANDWIDTH                 = 6, // Freeing bandwith error
	XI_READBLK                        = 7, // Read block error
	XI_WRITEBLK                       = 8, // Write block error
	XI_NO_IMAGE                       = 9, // No image
	XI_TIMEOUT                        =10, // Timeout
	XI_INVALID_ARG                    =11, // Invalid arguments supplied
	XI_NOT_SUPPORTED                  =12, // Not supported
	XI_ISOCH_ATTACH_BUFFERS           =13, // Attach buffers error
	XI_GET_OVERLAPPED_RESULT          =14, // Overlapped result
	XI_MEMORY_ALLOCATION              =15, // Memory allocation error
	XI_DLLCONTEXTISNULL               =16, // DLL context is NULL
	XI_DLLCONTEXTISNONZERO            =17, // DLL context is non zero
	XI_DLLCONTEXTEXIST                =18, // DLL context exists
	XI_TOOMANYDEVICES                 =19, // Too many devices connected
	XI_ERRORCAMCONTEXT                =20, // Camera context error
	XI_UNKNOWN_HARDWARE               =21, // Unknown hardware
	XI_INVALID_TM_FILE                =22, // Invalid TM file
	XI_INVALID_TM_TAG                 =23, // Invalid TM tag
	XI_INCOMPLETE_TM                  =24, // Incomplete TM
	XI_BUS_RESET_FAILED               =25, // Bus reset error
	XI_NOT_IMPLEMENTED                =26, // Not implemented
	XI_SHADING_TOOBRIGHT              =27, // Shading too bright
	XI_SHADING_TOODARK                =28, // Shading too dark
	XI_TOO_LOW_GAIN                   =29, // Gain is too low
	XI_INVALID_BPL                    =30, // Invalid bad pixel list
	XI_BPL_REALLOC                    =31, // Bad pixel list realloc error
	XI_INVALID_PIXEL_LIST             =32, // Invalid pixel list
	XI_INVALID_FFS                    =33, // Invalid Flash File System
	XI_INVALID_PROFILE                =34, // Invalid profile
	XI_INVALID_CALIBRATION            =35, // Invalid calibration
	XI_INVALID_BUFFER                 =36, // Invalid buffer
	XI_INVALID_DATA                   =38, // Invalid data
	XI_TGBUSY                         =39, // Timing generator is busy
	XI_IO_WRONG                       =40, // Wrong operation open/write/read/close
	XI_ACQUISITION_ALREADY_UP         =41, // Acquisition already started
	XI_OLD_DRIVER_VERSION             =42, // Old version of device driver installed to the system.
	XI_GET_LAST_ERROR                 =43, // To get error code please call GetLastError function.
	XI_CANT_PROCESS                   =44, // Data can't be processed
	XI_ACQUISITION_STOPED             =45, // Acquisition has been stopped. It should be started before GetImage.
	XI_ACQUISITION_STOPED_WERR        =46, // Acquisition has been stoped with error.
	XI_INVALID_INPUT_ICC_PROFILE      =47, // Input ICC profile missed or corrupted
	XI_INVALID_OUTPUT_ICC_PROFILE     =48, // Output ICC profile missed or corrupted
	XI_DEVICE_NOT_READY               =49, // Device not ready to operate
	XI_SHADING_TOOCONTRAST            =50, // Shading too contrast
	XI_ALREADY_INITIALIZED            =51, // Modile already initialized
	XI_NOT_ENOUGH_PRIVILEGES          =52, // Application doesn't enough privileges(one or more app
	XI_NOT_COMPATIBLE_DRIVER          =53, // Installed driver not compatible with current software
	XI_TM_INVALID_RESOURCE            =54, // TM file was not loaded successfully from resources
	XI_UNKNOWN_PARAM                  =100, // Unknown parameter
	XI_WRONG_PARAM_VALUE              =101, // Wrong parameter value
	XI_WRONG_PARAM_TYPE               =103, // Wrong parameter type
	XI_WRONG_PARAM_SIZE               =104, // Wrong parameter size
	XI_BUFFER_TOO_SMALL               =105, // Input buffer too small
	XI_NOT_SUPPORTED_PARAM            =106, // Parameter info not supported
	XI_NOT_SUPPORTED_PARAM_INFO       =107, // Parameter info not supported
	XI_NOT_SUPPORTED_DATA_FORMAT      =108, // Data format not supported
	XI_READ_ONLY_PARAM                =109, // Read only parameter
	XI_NO_DEVICES_FOUND               =110, // No devices found
	XI_BANDWIDTH_NOT_SUPPORTED        =111, // This camera does not support currently available bandwidth
	
}XI_RET;

//-------------------------------------------------------------------------------------------------------------------
// xiAPI enumerators
// structure containing information about output image format
typedef enum
{
	XI_MONO8                     =0, // 8 bits per pixel
	XI_MONO16                    =1, // 16 bits per pixel
	XI_RGB24                     =2, // RGB data format
	XI_RGB32                     =3, // RGBA data format
	XI_RGB_PLANAR                =4, // RGB planar data format
	XI_RAW8                      =5, // 8 bits per pixel raw data from sensor
	XI_RAW16                     =6, // 16 bits per pixel raw data from sensor
	
} XI_IMG_FORMAT;

// structure containing information about bayer color matrix
typedef enum
{
	XI_CFA_NONE                  =0, //  B/W sensors
	XI_CFA_BAYER_RGGB            =1, // Regular RGGB
	XI_CFA_CMYG                  =2, // AK Sony sens
	XI_CFA_RGR                   =3, // 2R+G readout
	XI_CFA_BAYER_BGGR            =4, // BGGR readout
	XI_CFA_BAYER_GRBG            =5, // GRBG readout
	XI_CFA_BAYER_GBRG            =6, // GBRG readout
	
} XI_COLOR_FILTER_ARRAY;

// structure containing information about buffer policy(can be safe, data will be copied to user/app buffer or unsafe, user will get internally allocated buffer without data copy).
typedef enum
{
	XI_BP_UNSAFE                 =0, // User gets pointer to internally allocated circle buffer and data may be overwritten by device.
	XI_BP_SAFE                   =1, // Data from device will be copied to user allocated buffer or xiApi allocated memory.
	
} XI_BP;

// structure containing information about trigger functionality
typedef enum
{
	XI_TRG_OFF                   =0, // Camera works in free run mode.
	XI_TRG_EDGE_RISING           =1, // External trigger (rising edge).
	XI_TRG_EDGE_FALLING          =2, // External trigger (falling edge).
	XI_TRG_SOFTWARE              =3, // Software(manual) trigger.
	XI_TRG_OUT                   =4, // Camera works in free run mode. Outputs sync sugnals.
	
} XI_TRG_SOURCE;

// structure containing information about GPI functionality
typedef enum
{
	XI_GPI_OFF                   =0, // Input off.
	XI_GPI_TRIGGER               =1, // Trigger input
	XI_GPI_EXT_EVENT             =2, // External signal input
	
} XI_GPI_MODE;

// structure containing information about GPO functionality
typedef enum
{
	XI_GPO_OFF                   =0, // Output off
	XI_GPO_ON                    =1, // Logical level.
	XI_GPO_FRAME_ACTIVE          =2, // On during exposure(integration) time
	XI_GPO_FRAME_ACTIVE_NEG      =3, // Off during exposure(integration) time
	XI_GPO_EXPOSURE_ACTIVE       =4, // On during exposure(integration) time
	XI_GPO_EXPOSURE_ACTIVE_NEG   =5, // Off during exposure(integration) time
	
} XI_GPO_MODE;

// structure containing information about LED functionality
typedef enum
{
	XI_LED_HEARTBEAT             =0, // set led to blink if link is ok, (led 1), heartbeat (led 2)
	XI_LED_TRIGGER_ACTIVE        =1, // set led to blink if trigger detected
	XI_LED_EXT_EVENT_ACTIVE      =2, // set led to blink if external signal detected
	XI_LED_ACQUISITION           =3, // set led to blink if data streaming
	XI_LED_EXPOSURE_ACTIVE       =4, // set led to blink if sensor integration time
	XI_LED_FRAME_ACTIVE          =5, // set led to blink if device busy/not busy
	XI_LED_LINK                  =6, // set led to blink if link is ok
	XI_LED_OFF                   =7, // set led to zero
	XI_LED_ON                    =8, // set led to one
	
} XI_LED_MODE;

// structure containing information about parameters type
typedef enum
{
	xiTypeInteger                =0, // integer parameter type
	xiTypeFloat                  =1, // float parameter type
	xiTypeString                 =2, // string parameter type
	
} XI_PRM_TYPE;

// Turn parameter On/Off
typedef enum
{
	XI_OFF                       =0, // Turn parameter off
	XI_ON                        =1, // Turn parameter on
	
} XI_SWITCH;

// Downsampling types
typedef enum
{
	XI_BINNING                   =0, // Downsampling is using  binning
	XI_SKIPPING                  =1, // Downsampling is using  skipping
	
} XI_DOWNSAMPLING_TYPE;

// structure containing information about CMS functionality
typedef enum
{
	XI_CMS_DIS                   =0, // CMS disable
	XI_CMS_EN                    =1, // CMS enable
	XI_CMS_EN_FAST               =2, // CMS enable(fast)
	
} XI_CMS_MODE;

//-------------------------------------------------------------------------------------------------------------------
// xiAPI structures
// structure containing information about incoming image.
typedef struct
{
	DWORD         size;      // Size of current structure on application side. When xiGetImage is called and size>=SIZE_XI_IMG_V2 then GPI_level, tsSec and tsUSec are filled.
	LPVOID        bp;        // pointer to data. If NULL, xiApi allocates new buffer.
	DWORD         bp_size;   // Filled buffer size. When buffer policy is set to XI_BP_SAFE, xiGetImage will fill this field with current size of image data received.
	XI_IMG_FORMAT frm;       // format of incoming data.
	DWORD         width;     // width of incoming image.
	DWORD         height;    // height of incoming image.
	DWORD         nframe;    // frame number(reset by exposure, gain, downsampling change).
	DWORD         tsSec;     // TimeStamp in seconds
	DWORD         tsUSec;    // TimeStamp in microseconds
	DWORD         GPI_level; // Input level
	
}XI_IMG, *LPXI_IMG;

//-------------------------------------------------------------------------------------------------------------------
// Global definitions

#define SIZE_XI_IMG_V1     28         // structure size default
#define SIZE_XI_IMG_V2     40         // structure size with timestamp and GPI level information
#define XI_PRM_INFO_MIN    ":min"     // Parameter minimum
#define XI_PRM_INFO_MAX    ":max"     // Parameter maximum
#define XI_PRM_INFO        ":info"    // Parameter value
/*************************************************************************************/
/**
   \brief Return number of discovered devices
   
   Returns the pointer to the number of all discovered devices.

   @param[out] pNumberDevices			number of discovered devices
   @return XI_OK on success, error value otherwise.
 */
XIAPI XI_RETURN __cdecl xiGetNumberDevices(OUT PDWORD pNumberDevices);
/**
   \brief Initialize device
   
   This function prepares the camera's software for work.
   It populates structures, runs initializing procedures, allocates resources - prepares the camera for work.

	\note Function creates and returns handle of the specified device. To de-initialize the camera and destroy the handler xiCloseDevice should be called.	

   @param[in] DevId						index of the device
   @param[out] hDevice					handle to device
   @return XI_OK on success, error value otherwise.
 */
XIAPI XI_RETURN __cdecl xiOpenDevice(IN DWORD DevId, OUT PHANDLE hDevice);
/**
   \brief Uninitialize device
   
   Closes camera handle and releases allocated resources.

   @param[in] hDevice					handle to device
   @return XI_OK on success, error value otherwise.
 */
XIAPI XI_RETURN __cdecl xiCloseDevice(IN HANDLE hDevice);
/**
   \brief Start image acquisition
   
   Begins the work cycle and starts data acquisition from the camera.

   @param[in] hDevice					handle to device
   @return XI_OK on success, error value otherwise.
 */
XIAPI XI_RETURN __cdecl xiStartAcquisition(IN HANDLE hDevice);
/**
   \brief Stop image acquisition
   
   Ends the work cycle of the camera and stops data acquisition.

   @param[in] hDevice					handle to device
   @return XI_OK on success, error value otherwise.
 */
XIAPI XI_RETURN __cdecl xiStopAcquisition(IN HANDLE hDevice);
/**
   \brief Return pointer to image structure
   
   Allows the user to retrieve the frame into LPXI_IMG structure.

   @param[in] hDevice					handle to device
   @param[in] timeout					time interval required to wait for the image (in milliseconds).
   @param[out] img						pointer to image info structure
   @return XI_OK on success, error value otherwise.
 */
XIAPI XI_RETURN __cdecl xiGetImage(IN HANDLE hDevice, IN DWORD timeout, OUT LPXI_IMG img);
/**
   \brief Set device parameter
   
   Allows the user to control device.

   @param[in] hDevice					handle to device
   @param[in] prm						parameter name string.
   @param[in] val						pointer to parameter set value.
   @param[in] size						size of val.
   @param[in] type						val data type.
   @return XI_OK on success, error value otherwise.
 */
XIAPI XI_RETURN __cdecl xiSetParam(IN HANDLE hDevice, const char* prm, void* val, DWORD size, XI_PRM_TYPE type);
/**
   \brief Get device parameter
   
   Allows the user to get the current device state and information.

   @param[in] hDevice					handle to device
   @param[in] prm						parameter name string.
   @param[in] val						pointer to parameter set value.
   @param[in] size						pointer to integer.
   @param[in] type						pointer to type container.
   @return XI_OK on success, error value otherwise.
 */
XIAPI XI_RETURN __cdecl xiGetParam(IN HANDLE hDevice, const char* prm, void* val, DWORD * size, XI_PRM_TYPE * type);

//Set device parameter
XIAPI XI_RETURN __cdecl xiSetParamInt(IN HANDLE hDevice, const char* prm, int val);
XIAPI XI_RETURN __cdecl xiSetParamFloat(IN HANDLE hDevice, const char* prm, float val);
XIAPI XI_RETURN __cdecl xiSetParamString(IN HANDLE hDevice, const char* prm, void* val, DWORD size);
/*-----------------------------------------------------------------------------------*/
//Get device parameter
XIAPI XI_RETURN __cdecl xiGetParamInt(IN HANDLE hDevice, const char* prm, int* val);
XIAPI XI_RETURN __cdecl xiGetParamFloat(IN HANDLE hDevice, const char* prm, float* val);
XIAPI XI_RETURN __cdecl xiGetParamString(IN HANDLE hDevice, const char* prm, void* val, DWORD size);

#ifdef __cplusplus
}
#endif

#endif /* __XIAPI_H */
