/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Simple Test Harness
//
// This test harness can be used to check out lower level functions
// This Harness DOES NOT include or use the Competition Functions
// nor Competition Template, see CompetitionHarness
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

// Since this is testing on the PC emulator, we'll force Mock Delays
// This overriddes the Mock Delays in the CoreAutoFunctions.c file.
#ifndef MOCK_DELAYS
#define MOCK_DELAYS
int mockDelays = 3000;
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
	driveForward(1000, 100);
	spinLeft(90, 100);
	driveForward(1000, 100);
	spinLeft(90, 100);
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
