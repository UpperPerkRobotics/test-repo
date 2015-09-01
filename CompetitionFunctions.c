/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Competition Functions
//
// This implements the Really Real functions that will be used in the competition
// They are implemented here so they can be used both by the TeamCompetitionTemplate
// AND the CompetitionHarness
//
//
// the CompetitionHarness allows replay / debugging / tweeking of these functions
//
/////////////////////////////////////////////////////////////////////////////////////////

#ifndef CODE_BASE
#define CODE_BASE
#include "CoreAutoFunctions.c"
#endif


//********************************************************************************
// Function used to allow picking of next Autonomous step, for super testing
//********************************************************************************
int getStepSelection(int currentStep, bool autoRun){
	//TODO: make this work with buttons;
	//TODO: Keep supporting emulation
	return currentStep;
}


//********************************************************************************
// This function is run once at the start of the match.
// Start Encoders, etc.
//********************************************************************************

void our_pre_auto(){

	writeDebugStreamLine("****** Starting Pre Auto Function **********************");


	// Important, first set the config.
	// This is used by CoreAutoFunctions to force Emulation, Disable motors, etc.
	setConfig();

	// Now do any other setup we want

	writeDebugStreamLine("****** Completed Pre Auto Function **********************");
}

////////////////////////////////////////////////////////////////////////////////////
// Autonomous Routine supports "controlled" running, to allow steps to be replayed,
// Speeds adjusted, and more.
////////////////////////////////////////////////////////////////////////////////////
void our_auto(bool autoRun){
	writeDebugStreamLine("****** Starting Autonomous Function **********************");

	int stepCounter = 0;

	if(!autoRun){
		writeDebugStreamLine("--- AutoRun == false ---- ");
	}

	// Increment this when there's more steps!
	while(stepCounter < 20){
		writeDebugStreamLine("--Step number: %d", stepCounter);
		getStepSelection(stepCounter, autoRun);
  // .....................................................................................
  // This is the OFFICIAL Autonomous Routine.  Experiments go in a "SimpleTestHarness"
  // .....................................................................................


			switch(stepCounter){
				case 0:
					driveForward(1005, 100);
					break;
				case 1:
					spinLeft(45, 100);
					break;
				case 2:
					driveForward(1000, 100);
					break;
				case 3:
					spinLeft(90, 100);
					break;
				default:
					writeDebugStreamLine("--Step number %d not defined", stepCounter);
			}

			stepCounter++;
	} // End While loop
	writeDebugStreamLine("****** Completed Autonomous Function **********************");
}

void our_userControl(){
	// User control code here, inside the loop
	writeDebugStreamLine("****** Started User Control Function **********************");
	while (true)
	{
	  // This is the main execution loop for the user control program. Each time through the loop
	  // your program should update motor + servo values based on feedback from the joysticks.

	  // .....................................................................................
	  // Insert user code here. This is where you use the joystick values to update your motors, etc.
	  // .....................................................................................
		writeDebugStreamLine("NO USER CODE YET, SO THIS WILL JUST HANG",);
		delay(1000);

	}
}
