/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Simple Measuring Test Harness
//
// This test harness disables the motors; it's used to test distances
// It can be used in emulation OK, but it's meant to figure out distances
//
// Use It with the Emulator First, to make sure coreFunctions Calculate as expected
// Then use the Robot, MOVE The Robot, and read the displayed encoder values.
// Hit a button to go to the next vesion block.

//
// Copy this and make as many simple harnesses as you want, it doesn't
// conflict with any other stuff.  Delete this whenever you want.
// Use these to experiement with new automous programs, or other functions under development
//
/////////////////////////////////////////////////////////////////////////////////////////

//*********************************************************************
// Test Harness-specific **Global Configuration Vaules**
//
// These control overall behavior of the code, allowing for advanced
// Debug, Test, Experiment behaviors
//*********************************************************************

// If this is emulated, the Manual Triggers doesn't get used; goes right to "Mock Sensors"

// Manual MOTORS!  Let's people have the fun of moving robot!
#ifndef REAL_MOTORS
#define REAL_MOTORS
bool areMotorsEnabled = false;
#endif

// Manual SENSORS!  You have to Trigger the sensor via a button on the controller.
#ifndef SENSOR_TYPE
#define SENSOR_TYPE
int useSensorType = 1; // Manual Triggers
#endif

// SENSOR LOGGING!  allows various levels to sensor logging.
#ifndef SENSOR_LOGGING
#define SENSOR_LOGGING
bool logAllSensors = false;
bool logActiveSensor = true;
#endif

// Need to pull in the Code Base for testing
#ifndef CODE_BASE
#define CODE_BASE
#include "CoreAutoFunctions.c"
#endif

//////////////////////////////////////////////////////////////////////////////
// End Standard Harness Configurations
//////////////////////////////////////////////////////////////////////////////


// Broken up as a seperate task, just for fun
// Could have easily just been part of the overall main task
task autoTestTask()
{
	driveForward(1005, 100);
}

task main()
{
	// Important, first set the config.
	// This is used by CoreAutoFunctions to force Emulation, Disable motors, etc.
	setConfig();


	// Now do fun stuff !!!
	startTask(autoTestTask);

	delay(200000);
}
