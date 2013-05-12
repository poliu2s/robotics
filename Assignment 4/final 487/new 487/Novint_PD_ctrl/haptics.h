// Make sure this header is included only once
#ifndef HAPTICS_H
#define HAPTICS_H

#include <hdl\hdl.h>
#include <hdlu\hdlu.h>

// Blocking values
const bool bNonBlocking = false;
const bool bBlocking = true;

class HapticsClass 
{

// Define callback functions as friends
friend HDLServoOpExitCode ContactCB(void *data);
friend HDLServoOpExitCode GetStateCB(void *data);

public:
    // Constructor
    HapticsClass();

    // Destructor
    ~HapticsClass();

    // Initialize
    void init();

    // Clean up
    void uninit();

    // Get position
    void getPosition(double pos[3]);

    // Get state of device button
    bool isButtonDown();

    // synchFromServo() is called from the application thread when it wants to exchange
    // data with the HapticClass object.  HDAL manages the thread synchronization
    // on behalf of the application.
    void synchFromServo();

    // Get ready state of device.
    bool isDeviceCalibrated();

	//Set force
	void setForce(double force[3]);

private:
    // Move data between servo and app variables
    void synch();

	//Calculate force
	void calcForce();

    // Matrix multiply
    void vecMultMatrix(double srcVec[3], double mat[16], double dstVec[3]);

    // Check error result; display message and abort, if any
    void testHDLError(const char* str);

    // Nothing happens until initialization is done
    bool m_inited;

	// Transformation from Device coordinates to Application coordinates
    double m_transformMat[16];
    
    // Variables used only by servo thread
    double m_positionServo[3];
    bool   m_buttonServo;
    double m_forceServo[3];

    // Variables used only by application thread
    double m_positionApp[3];
    bool   m_buttonApp;

	//Constant force applied
	double m_forceApp[3];

    // Handle to device
    HDLDeviceHandle m_deviceHandle;

    // Handle to Contact Callback 
    HDLServoOpExitCode m_servoOp;

    // Device workspace dimensions
    double m_workspaceDims[6];
};

// External declaration for class instance global storage
extern HapticsClass *hapticsVar;

// Method wrappers
extern void createHaptics();

extern void deleteHaptics();

extern void falconPlant(double force[3], double position[3]);

#endif // HAPTICS_H