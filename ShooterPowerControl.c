#pragma config(Sensor, dgtl4,  leftShooter,    sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  rightShooter,   sensorQuadEncoder)
#pragma config(Motor,  port2,           leftDrive,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightDrive,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           leftTopShooter, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           rightTopShooter, tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "Filter.c"
#include "RobotPowerTable.c"


// Global Variables for shooter control
// These are set by the joystick methods
int shooter_target_speed = 0;

task shooter_power_control(){

	int last_right_clicks = 0;
	int last_left_clicks = 0;
	int last_read_time = -10;

	int print_value = 0;

	int left_power = 0;
	int right_power = 0;


	while(true)
	{

		// Variables for power control
		int current_right_clicks = SensorValue[rightShooter];
		int current_left_clicks = SensorValue[leftShooter];
		int current_read_time = nPgmTime;

		// current raw speed
		int elapsed_right_clicks = current_right_clicks - last_right_clicks;
		int elapsed_left_clicks = current_left_clicks - last_left_clicks;
		// int elapsed_time = current_read_time - last_read_time;

		// filtered speed
		int current_right_speed = filterRight(elapsed_right_clicks);
		int current_left_speed = filterLeft(elapsed_left_clicks);


		// Do power control with filtered values;

		if(shooter_target_speed == 0){
			right_power = 0;
		}
		else if(current_right_speed < (shooter_target_speed * 0.9)){
			right_power = 127;
		}
		else if(current_right_speed > (shooter_target_speed * 1.1)){
			right_power = getRightShooterPower(shooter_target_speed);
		}
		else if(current_right_speed < (shooter_target_speed * 0.98)){
			right_power = right_power++;
		}
		else if(current_right_speed > (shooter_target_speed * 1.02)){
			right_power = --right_power;
		}


		if(shooter_target_speed == 0){
			left_power = 0;
		}
		else if(current_left_speed < (shooter_target_speed * 0.9)){
			left_power = 127;
		}
		else if(current_left_speed > (shooter_target_speed * 1.1)){
			left_power = getLeftShooterPower(shooter_target_speed);
		}
		else if(current_left_speed < (shooter_target_speed * 0.98)){
			left_power = left_power++;
		}
		else if(current_left_speed > (shooter_target_speed * 1.02)){
			left_power = --left_power;
		}

		// TODO: Control motor power
		motor[leftTopShooter] = left_power;
		motor[rightTopShooter] = right_power;


		// End of poser control work.

		// Save values for next reading time.
			last_left_clicks = current_left_clicks;
			last_right_clicks = current_right_clicks;
			last_read_time = current_read_time;

			delay(100);

			print_value = (print_value + 1);
			if(print_value == 1){
				//writeDebugStreamLine("current_right_clicks: %d", current_right_clicks);
				//writeDebugStreamLine("elapsed_right_clicks: %d", elapsed_right_clicks);
				//writeDebugStreamLine("elapsed_time: %d", elapsed_time);
				//writeDebugStreamLine("current_read_time: %d", current_read_time);
				writeDebugStreamLine("************************************");
				writeDebugStreamLine("shooter_target_speed: %d", shooter_target_speed);
				writeDebugStreamLine("left shooter power: %d", left_power);
				writeDebugStreamLine("current_left_speed: %d", current_left_speed);
				writeDebugStreamLine("right shooter power: %d", right_power);
				writeDebugStreamLine("current_right_speed: %d", current_right_speed);

				print_value = 0;
			}

	}
}

void set_shooter_targets(int speed){
	// For now, set value and print a debug statement
	shooter_target_speed = speed;
	// shooter_target_power = power;
	writeDebugStreamLine("Shooter Target Speed: %d", shooter_target_speed);
}

void adjust_shooter_targets(int adjust_speed){
	// For now, adjust value a bit, and print a debug statement
	shooter_target_speed = shooter_target_speed + adjust_speed;
	// shooter_target_power = shooter_target_power + adjust_power;
	writeDebugStreamLine("Shooter Target Speed: %d", shooter_target_speed);
}

// Read Buttons to see if any are pushed
task controllerPolling(){
	while(true){
		// Check each button and do actions
		if(vexRT[Btn8U] == 1){
			// Set motor target speed (Far), Channel 8, Button U
			set_shooter_targets(700);
			delay(500);
		}
		else if(vexRT[Btn8R] == 1){
			// Set motor target speed (Medium), Channel 8, Button R
			set_shooter_targets(160);
			delay(500);
		}
		else if(vexRT[Btn8D] == 1){
			// Set motor target speed (Short), Channel 8, Button D
			set_shooter_targets(88);
			delay(500);
		}
		else if(vexRT[Btn6U] == 1){
			// Adjust motor target speed (5 up), Channel 6, Button U
			adjust_shooter_targets(4);
			delay(250);
		}
		else if(vexRT[Btn6D] == 1){
			// Adjust motor target speed (5 down), Channel 6, Button D
			adjust_shooter_targets(-4);
			delay(250);
		}
		else if(vexRT[Btn8L] == 1){
			// Stop all motor speed (0), Channel 8, Button L
			set_shooter_targets(0);
			delay(500);
		}
		delay(10);
	}
}

// Add driver joystick Controls here
task driving(){
	while(true)
	{

		//writeDebugStreamLine("***** Drive Loop ******");
		if((vexRT[Ch2] > 20) || (vexRT[Ch2] < -20))
		{
			//writeDebugStreamLine("***** Right Side Go ******");
			motor[rightDrive] = vexRT[Ch2];
		}
		else {
			motor[rightDrive] = 0;
		}

		if((vexRT[Ch3] > 20) || (vexRT[Ch3] < - 20))
		{
			motor[leftDrive] = vexRT[Ch3];
		}
		else {
			motor[leftDrive] = 0;
		}

		delay(50);
	}
}


// End Driver joystick Controls
task main()
{
startTask(shooter_power_control);
startTask(controllerPolling);
startTask(driving);
while(true)
	{
	delay(100000);
	}
}
