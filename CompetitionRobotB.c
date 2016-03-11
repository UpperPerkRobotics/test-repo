#pragma config(Motor,  port2,           leftDrive,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightDrive,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           strafeDrive,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           strafeFront,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           expeller,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           intake,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           shooterLeft,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           shooterRight,  tmotorVex393_MC29, openLoop)
#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!
#include "DriverJoystickControlRobotB.c"

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
  bStopTasksBetweenModes = true;
  bLCDBacklight = true;
	displayLCDCenteredString(0, "Calibrating Gyro");
	SensorType[in1] = sensorNone;
	wait1Msec(1000);
	displayLCDCenteredString(1, "50% Complete");
	SensorType[in1]= sensorGyro;
	wait1Msec(2000);
	displayLCDCenteredString(0, "Gyro Ready");
	clearLCDLine(1);
	bLCDBacklight = false;

}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	displayLCDCenteredString(0, "Autonomous Mode");

	// Fire ball
	// Turn on Shooter for 2 seconds
	motor[shooterLeft] = 127;
	motor[shooterRight] = -127;
	wait1Msec(2000);
	// Turn off Shooter
	motor[shooterLeft] = 0;
	motor[shooterRight] = 0;

	// Then drive forward with intake and what for 4 seconds
	SensorValue[in1] = 0;
	motor[intake] = 127;
	for (int i=0; i < 2000; i++){
		motor[rightDrive] 	= 100 - (SensorValue[in1] / 4);
		motor[leftDrive] 		= 100 + (SensorValue[in1] / 4);
		wait1Msec(2);
	}

	// Then Turn off everything
	motor[rightDrive] 	= 0;
	motor[leftDrive] 		= 0;
	motor[intake] = 0;


}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	// User control code here, inside the loop
	displayLCDCenteredString(0, "User Control");
	// User Control
	startTask(controllerPolling);
	startTask(driving);
	while(true)
	{
		displayLCDCenteredString(0, "User Control");
		delay(2000);
	}
}
