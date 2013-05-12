#include "haptics.h"
#include <windows.h>
#include <math.h>
#include <iostream>
#include <fstream>

//ofstream cout("sfunc_debug.txt");

/***************************************/
/**** Class instance global storage ****/
/***************************************/

HapticsClass *hapticsVar;

/**********************************/
/**** Class method definitions ****/
/**********************************/
// Continuous servo callback function
HDLServoOpExitCode ContactCB(void* pUserData)
{
    // Get pointer to haptics object
    HapticsClass* haptics = static_cast< HapticsClass* >( pUserData );

    // Get current state of haptic device
    hdlToolPosition(haptics->m_positionServo);
    hdlToolButton(&(haptics->m_buttonServo));


	haptics->calcForce();

    // Send forces to device
    hdlSetToolForce(haptics->m_forceServo);

    // Make sure to continue processing
    return HDL_SERVOOP_CONTINUE;
}

// On-demand synchronization callback function
HDLServoOpExitCode GetStateCB(void* pUserData)
{
    // Get pointer to haptics object
    HapticsClass* haptics = static_cast< HapticsClass* >( pUserData );

    // Call the function that copies data between servo side 
    // and client side
    haptics->synch();

    // Only do this once.  The application will decide when it
    // wants to do it again, and call CreateServoOp with
    // bBlocking = true
    return HDL_SERVOOP_EXIT;
}

// Constructor--just make sure needed variables are initialized.
HapticsClass::HapticsClass()
    : m_deviceHandle(HDL_INVALID_HANDLE),
      m_servoOp(HDL_INVALID_HANDLE),
      m_inited(false)
{
    for (int i = 0; i < 3; i++)
	{
        m_positionServo[i] = 0;
		m_forceApp[i] = 0;
	}
}

// Destructor--make sure devices are uninited.
HapticsClass::~HapticsClass()
{
    uninit();
}



void HapticsClass::init()
{
    HDLError err = HDL_NO_ERROR;

    // Passing "DEFAULT" or 0 initializes the default device based on the
    // [DEFAULT] section of HDAL.INI.   The names of other sections of HDAL.INI
    // could be passed instead, allowing run-time control of different devices
    // or the same device with different parameters.  See HDAL.INI for details.
    m_deviceHandle = hdlInitNamedDevice("DEFAULT");
    testHDLError("hdlInitDevice");

    if (m_deviceHandle == HDL_INVALID_HANDLE)
    {
		std::cout << "Could not open device" << " " << "Device Failure" << std::endl;
        exit(0);
    }

    // Now that the device is fully initialized, start the servo thread.
    // Failing to do this will result in a non-funtional haptics application.
    hdlStart();
    testHDLError("hdlStart");

    // Set up callback function
    m_servoOp = hdlCreateServoOp(ContactCB, this, bNonBlocking);
    if (m_servoOp == HDL_INVALID_HANDLE)
    {
       std::cout <<  "Invalid servo op handle" << " " << "Device Failure" << std::endl;
	   exit(0);
    }
    testHDLError("hdlCreateServoOp");

    // Make the device current.  All subsequent calls will
    // be directed towards the current device.
    hdlMakeCurrent(m_deviceHandle);
    testHDLError("hdlMakeCurrent");

    // Get the extents of the device workspace.
    // Used to create the mapping between device and application coordinates.
    // Returned dimensions in the array are minx, miny, minz, maxx, maxy, maxz
    //                                      left, bottom, far, right, top, near)
    // Right-handed coordinates:
    //   left-right is the x-axis, right is greater than left
    //   bottom-top is the y-axis, top is greater than bottom
    //   near-far is the z-axis, near is greater than far
    // workspace center is (0,0,0)
    hdlDeviceWorkspace(m_workspaceDims);
    testHDLError("hdlDeviceWorkspace");


    // Establish the transformation from device space to app space
    // To keep things simple, we will define the app space units as
    // inches, and set the workspace to approximate the physical
    // workspace of the Falcon.  That is, a 4" cube centered on the
    // origin.  Note the Z axis values; this has the effect of
    // moving the origin of world coordinates toward the base of the
    // unit.
    double gameWorkspace[] = {-2,-2,-2,2,2,3};
    bool useUniformScale = true;
    hdluGenerateHapticToAppWorkspaceTransform(m_workspaceDims,
                                              gameWorkspace,
                                              useUniformScale,
                                              m_transformMat);
    testHDLError("hdluGenerateHapticToAppWorkspaceTransform");


    m_inited = true;
}

// uninit() undoes the setup in reverse order.  Note the setting of
// handles.  This prevents a problem if uninit() is called
// more than once.
void HapticsClass::uninit()
{
    if (m_servoOp != HDL_INVALID_HANDLE)
    {
        hdlDestroyServoOp(m_servoOp);
        m_servoOp = HDL_INVALID_HANDLE;
    }
    hdlStop();
    if (m_deviceHandle != HDL_INVALID_HANDLE)
    {
        hdlUninitDevice(m_deviceHandle);
        m_deviceHandle = HDL_INVALID_HANDLE;
    }
    m_inited = false;
}

// This is a simple function for testing error returns.  A production
// application would need to be more sophisticated than this.
void HapticsClass::testHDLError(const char* str)
{
    HDLError err = hdlGetError();
    if (err != HDL_NO_ERROR)
    {
		std::cout << "HDAL ERROR"  << std::endl;
        abort();
    }
}

// This is the entry point used by the application to synchronize
// data access to the device.  Using this function eliminates the 
// need for the application to worry abcout threads.
void HapticsClass::synchFromServo()
{
    hdlCreateServoOp(GetStateCB, this, bBlocking);
}

// GetStateCB calls this function to do the actual data movement.
void HapticsClass::synch()
{


    m_buttonApp = m_buttonServo;
}

// A utility function to handle matrix multiplication.  A production application
// would have a full vector/matrix math library at its disposal, but this is a
// simplified example.
void HapticsClass::vecMultMatrix(double srcVec[3], double mat[16], double dstVec[3])
{
    dstVec[0] = mat[0] * srcVec[0] 
        + mat[4] * srcVec[1]
        + mat[8] * srcVec[2]
        + mat[12];
    
    dstVec[1] = mat[1] * srcVec[0]
        + mat[5] * srcVec[1]
        + mat[9] * srcVec[2]
        + mat[13];

    dstVec[2] = mat[2] * srcVec[0]
        + mat[6] * srcVec[1]
        + mat[10] * srcVec[2]
        + mat[14];
}

//Function to calculate applied forces.
void HapticsClass::calcForce()
{
	// Convert from device coordinates to application coordinates.
    vecMultMatrix(m_positionServo, m_transformMat, m_positionApp);

	//Apply forces

    m_forceServo[0] = m_forceApp[0]; 
    m_forceServo[1] = m_forceApp[1]; 
    m_forceServo[2] = m_forceApp[2];
}

// Interface function to get current position
void HapticsClass::getPosition(double pos[3])
{
    pos[0] = m_positionApp[0];
    pos[1] = m_positionApp[1];
    pos[2] = m_positionApp[2];

}

// Interface function to get button state.  Only one button is used
// in this application.
bool HapticsClass::isButtonDown()
{
    return m_buttonApp;
}

// For this application, the only device status of interest is the
// calibration status.  A different application may want to test for
// HDAL_UNINITIALIZED and/or HDAL_SERVO_NOT_STARTED
bool HapticsClass::isDeviceCalibrated()
{
    unsigned int state = hdlGetState();

	std::cout << state << std::endl;

    return ((state & HDAL_NOT_CALIBRATED) == 0);
}

void HapticsClass::setForce(double force[3])
{
	//Copy forces
    m_forceApp[0] = force[0]; 
    m_forceApp[1] = force[1]; 
    m_forceApp[2] = force[2];

}

//*************************************************
//**** Wrappers for methods called in Simulink ****
//*************************************************
void createHaptics()
{
	hapticsVar = new HapticsClass;
    hapticsVar->init();
}

void deleteHaptics()
{
	delete hapticsVar;
}

void falconPlant(double force[3], double position[3])
{
   hapticsVar->setForce(force);
   for (int i = 0; i < 3; i++)
       hapticsVar->getPosition(position);
}