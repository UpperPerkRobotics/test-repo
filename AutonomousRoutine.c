#pragma config(Sensor, dgtl1,  GreenLight,     sensorLEDtoVCC)
#pragma config(Sensor, dgtl2,  YellowLight,    sensorLEDtoVCC)
#pragma config(Sensor, dgtl3,  RedLight,       sensorLEDtoVCC)
#pragma config(Sensor, dgtl4,  leftShooter,    sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  rightShooter,   sensorQuadEncoder)
#pragma config(Sensor, dgtl8,  drive,          sensorQuadEncoder)
#pragma config(Sensor, dgtl11, FrontLED,       sensorLEDtoVCC)
#pragma config(Sensor, dgtl12, BackLED,        sensorLEDtoVCC)
#pragma config(Motor,  port2,           leftDrive,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightDrive,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           Intake,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           Puncher,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           strafe,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           rightLifter,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           leftTopShooter, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           rightTopShooter, tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(105)

#include "HeadLightControl.c"
#include "AutoShooting.c"
//#include "AutoShootingSimple.c"
#include "pidShooterControl.c"
//#include "ShooterPowerControlV4.c"
#include "DriverJoystickControls.c"
#include "Vex_Competition_Includes.c"

void pre_auton()
{
	bStopTasksBetweenModes = true;
}

task autonomous()
{
	set_shooter_targets(57);
	startTask(shooter_power_control);
	startTask(AutoIntake);
	delay(13000);
	hipshot = true;
	//simpleAutoIntake(5);
	//if(SensorValue[Jumper] == 1){
	//set_shooter_targets(0);
		//spinLeft();
	// 	}
	//else {
		//simpleAutoIntake(5);
	// }
}

task usercontrol()
{
	stopTask(AutoIntake);
	startTask(shooter_power_control);
	startTask(controllerPolling);
	startTask(driving);
	setHeadLights(driveTrainReversed);
	while (true)
	{
		delay(100000);
	}
}
