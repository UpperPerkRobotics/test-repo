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
#pragma config(Motor,  port4,           leftIntake,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           rightIntake,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           leftLifter,    tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           rightLifter,   tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           leftTopShooter, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           rightTopShooter, tmotorVex393_MC29, openLoop, reversed)


void spinLeft(){

// reset Enconder
SensorValue[drive] = 0;
// while Loop
while( SensorValue[drive] < 300){
	// set motors
	motor[leftDrive] = 50;
	motor[rightDrive] = -50;
		// delay
	delay (20);
	}
// stop motors
motor[leftDrive] = 0;
motor[rightDrive] = 0;

}


task main()
{
	spinLeft();
}
