#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "CompetitionFunctions.c"

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          DON'T MODIFY THIS FILE
//
//	REAL STUFF is in "CompetitionFunctions.c"
//
//	This is used by the field to call our functions.  But we don't want to put our real
// stuff right in here, so that we have more testing control.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
  our_pre_auto();
}

task autonomous()
{
	// auto Run
	our_auto(true);
}


task usercontrol()
{
	our_userControl();
}
