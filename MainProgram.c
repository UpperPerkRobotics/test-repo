#pragma config(Sensor, dgtl1,  GreenLight,     sensorLEDtoVCC)
#pragma config(Sensor, dgtl2,  YellowLight,    sensorLEDtoVCC)
#pragma config(Sensor, dgtl3,  RedLight,       sensorLEDtoVCC)
#pragma config(Sensor, dgtl4,  leftShooter,    sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  rightShooter,   sensorQuadEncoder)
#pragma config(Sensor, dgtl11, FrontLED,       sensorLEDtoVCC)
#pragma config(Sensor, dgtl12, BackLED,        sensorLEDtoVCC)
#pragma config(Motor,  port2,           leftDrive,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightDrive,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           leftIntake,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           rightIntake,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           leftLifter,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           rightLifter,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           leftTopShooter, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           rightTopShooter, tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "HeadLightControl.c"
#include "AutoShooting.c"
#include "ShooterPowerControlV4.c"
#include "DriverJoystickControls.c"
task main()
{
	setHeadLights(driveTrainReversed);

// Fake Autonomous
	startTask(shooter_power_control);
	set_shooter_targets(910);
	startTask(AutoIntake);
	delay(15000);
	stopAllTasks();

	// User Control
	startTask(shooter_power_control);
	startTask(controllerPolling);
	startTask(driving);

	while(true)
	{
		delay(105000);
	}
}
