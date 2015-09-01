

/////////////////////////////////////////////////////////////////////////////////////////////////
//
// CoreAutoFunctions
//
// Basic Autonomous functions used by higher level functions
//
////////////////////////////////////////////////////////////////////////////////////////////////


///*******************************************************************************
// Global Configuration Items
//
// These setting enable special behaviors for debugging, prototyping, and test purposes
// Guards used as they could be overriden in harnesses
///*******************************************************************************

// delays used for motor movements, etc. when using PC emulator
#ifndef MOCK_DELAYS
#define MOCK_DELAYS
int mockDelays = 3000;
#endif

// Manual MOTORS!  If set to "false" let's people have the fun of moving robot!
#ifndef REAL_MOTORS
#define REAL_MOTORS
bool areMotorsEnabled = true;
#endif

// Manual SENSORS!  If set to "false" let's people have the fun of triggering sensor events remote!
#ifndef SENSOR_TYPE
#define SENSOR_TYPE
int useSensorType = 0; // 0 = Real Sensors, 1 = Manual Triggers, 2 = Mock Sensors
#endif

// SENSOR LOGGING!  allows various levels to sensor logging.
#ifndef SENSOR_LOGGING
#define SENSOR_LOGGING
bool logAllSensors = false;
bool logActiveSensor = false;
#endif


// End of Global Config Items ****************************************************

//*******************************************************************************
// MAGIC NUMBERS
//
// These magic numbers are used on by these low level functions, and include stuff
// like the number of encoder clicks required to turn 1 degree left.
// ******************************************************************************
//
//
static const int DRIVE_FORWARD_CLICKS_PER_10CM = 25;
static const int SPIN_LEFT_CLICKS_PER_DEGREE = 5;



///////////////////////////////////////////////////////////////////////
// Function - setConfig
//
// Prints out the effective configuration
// Supports fixing configuration when it's not right (say Emulatored vs Cortex)
// Can do more later
//////////////////////////////////////////////////////////////////////
void setConfig(){

	writeDebugStreamLine("******** SETTING CONFIGURATION **************");
	if (strcmp(_TARGET, "Emulator") == 0)
	{
		writeDebugStreamLine("------ Target is Emulator");
		writeDebugStreamLine("--------- Disabling Motors and Sensors");

		areMotorsEnabled = false;
		useSensorType = 2;
		writeDebugStreamLine("--------- Using Mock Delays: %d", mockDelays);
	}
	writeDebugStreamLine("-- REAL_MOTORS: %s",
												(areMotorsEnabled ? "true" : "false"));
	writeDebugStreamLine("-- SENSOR_TYPE: %d", useSensorType);
	writeDebugStreamLine("-- LOGGING All Sensors: %s",
												(logAllSensors ? "true" : "false" ));
	writeDebugStreamLine("-- LOGGING Active Sensor: %s",
												(logActiveSensor ? "true" : "false" ));
	writeDebugStreamLine("******** END CONFIGURATION **************");
}

///////////////////////////////////////////////////////////////////////
// Function - keepRunning
//
// Used by Functions to abstract away common 'sensor code'
// Supports functions that need to compare a current encoder value to a target value
//
// Evaluates to true if this should keep running.  Used to wrap the
// Different Sensor types
//
// If sensor types = 0, this will evaluate and decide
// If sensor types = 1, this will check for a button press to quit
// If sensor types = 2, this will delay for MOCK DELAYS, then say to quit
//////////////////////////////////////////////////////////////////////

bool keepRunning( int currentClicks, int destClicks){
	switch(useSensorType)
		{
			case 0: // Real Sensors
				return (currentClicks < destClicks);
			case 1: // Manual Sensors
				writeDebugStreamLine("---- Manual Sensors - block runs until controller button pressed");
				// TODO: POLL FOR A BUTTON PRESS
				return false;
			case 2: // MOCK SENSORS
				writeDebugStreamLine("---- Mock Sensors - delay for MOCK_DELAYS");
				delay(mockDelays);
				return false;
		default:
			writeDebugStreamLine("--- Invalid SensorType");
			return false;
	}
}


///////////////////////////////////////////////////////////////////////
// Awesome Common Autonomous Blocks!!!!
//
// Can be used in real robots, Emulator, or manual motors/sensor configurations
// This allows the block to be used to program an autonmous routine right on the PC,
// or use the Robot to measure real desired distances, etc.
//
//////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////
// drive forward
///////////////////////////////////////////////////
void driveForward(int distanceCM, int power){
	writeDebugStreamLine("-- Driving Forward, %d Centimeters", distanceCM);

	// 1.  First Calculate how far this should need to go, in clicks
	int distanceInClicks = (int)(((float) distanceCM / 10) * DRIVE_FORWARD_CLICKS_PER_10CM);
	writeDebugStreamLine("--- Calculated, %d Clicks", distanceInClicks);

	// 2.  Where are we starting at, exactly in clicks?
	int startingClicks = 0;
	// For the physical Robot, get the real starting clicks on the encoder
	if ((useSensorType == 0) || (useSensorType == 1)){
		// TODO: Set startingClicks to the real starting encoder value
	}
	writeDebugStreamLine("--- Starting Encoder Value, %d Clicks", startingClicks);

	// 3.  Now, we call tell when we should be able to stop driving
	int currentClicks = startingClicks;
	int destClicks = startingClicks + distanceInClicks;
	writeDebugStreamLine("--- Destination Encoder Value, %d Clicks", destClicks);

	// 4. CONTROL EXECUTION
	if (! areMotorsEnabled){
		writeDebugStreamLine("--- MOTORS DISABLED, push if you want");
	}
	while (keepRunning(currentClicks, destClicks)){
		if (areMotorsEnabled) {
			// TODO: Turn on Proper Motors
			delay(50);
			// TODO: GET CURRENT CLICKS
			if (logActiveSensor)
				writeDebugStreamLine("---- Currect Click Count: %d", currentClicks);
		}
	}
	writeDebugStreamLine("- Completed Drive Forward");
}

//////////////////////////////////////////////////////////////////////////
// robot pivots in place, to the left.
//////////////////////////////////////////////////////////////////////////
void spinLeft(int degrees, int power){

	writeDebugStreamLine("- Starting Spin Left, %d Degrees", degrees);

	// 1.  First Calculate how far this should need to go, in clicks
	int distanceInClicks = degrees * SPIN_LEFT_CLICKS_PER_DEGREE;

	writeDebugStreamLine("--- Calculated, %d Clicks", distanceInClicks);

	// 2.  Where are we starting at, exactly in clicks?
	int startingClicks = 0;
	// For the physical Robot, get the real starting clicks on the encoder
	if ((useSensorType == 0) || (useSensorType == 1)){
		// TODO: Set startingClicks to the real starting encoder value
	}
	writeDebugStreamLine("--- Starting Encoder Value, %d Clicks", startingClicks);

	// 3.  Now, we call tell when we should be able to stop driving
	int currentClicks = startingClicks;
	int destClicks = startingClicks + distanceInClicks;
	writeDebugStreamLine("--- Destination Encoder Value, %d Clicks", destClicks);


	// 4. CONTROL EXECUTION
	if (! areMotorsEnabled){
		writeDebugStreamLine("--- MOTORS DISABLED, push if you want");
	}
	while (keepRunning(currentClicks, destClicks)){
		if (areMotorsEnabled) {
			// TODO: Turn on Proper Motors
			delay(50);
			// TODO: GET CURRENT CLICKS
			if (logActiveSensor)
				writeDebugStreamLine("---- Currect Click Count: %d", currentClicks);
		}
	}		writeDebugStreamLine("- Completed Spin Left");
}
