#include "Filter.c"
#include "RealRobotPowerTable.c"
#include "StopLightControl.c"
#include "StableCheck.c"

int shooter_target_speed = 0;

// Global Variables for shooter control
// These are set by the joystick methods

task shooter_power_control(){

bool recoveringRight = false;
bool recoveringLeft = false;


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
		int current_right_speed = elapsed_right_clicks * 5;
		int current_left_speed = elapsed_left_clicks * 5;


		// Stoplight color controls
		int left_color = NONE;
		int right_color = NONE;

		// Do power control with filtered values;

		if(shooter_target_speed == 0){
			right_color = NONE;
			right_power = 0;
		}

		// Right Side Speed Control
		// Right Side is in recovery mode
		if (recoveringRight){
			// In recovery mode, we use max power until we reach 95% of target speed
			if(current_right_speed > (shooter_target_speed * 0.95)){
				recoveringRight = false;
				right_color = YELLOW;
				right_power = getRightShooterPower(shooter_target_speed);
			}
			// We're not at 95% yet, so keep recovering
			else{
				right_color = RED;
				right_power = 127;
			}
		}
		// Else in Normal mode
		else{
		// In normal mode, we use the lookup table
		// We make small adjustments (but not yet)
		// And we may move to recovery mode

		// Speed is LESS THAN 85% of target speed
		if(current_right_speed < (shooter_target_speed * 0.85)){
			recoveringRight = true;
			right_color = RED;
			right_power = 127;
		}

		// Otherwise use canned numbers
		else {
			right_power = getRightShooterPower(shooter_target_speed);

			if (isRightStable(right_power)){
				purgeRightValues();
				// Print out "Right side stable @ what power, and what speed"
				writeDebugStreamLine("Right side stable at %d speed", current_right_speed);
				writeDebugStreamLine("Right side stable at %d power", right_power);
			}

			// Now just set the colors
			// Speed is between 1% above or below target
			if(current_right_speed < (shooter_target_speed * 0.99)){
				right_color = YELLOW;
			}
			else if(current_right_speed > (shooter_target_speed * 1.01)){
				right_color = YELLOW;
			}
			// Speed is in the 2% sweet spot
			else {
				right_color = GREEN;
			}
		}
	}
		// End of Right side Speed Control

		// Left Side Speed Control
		// Left Side is in recovery mode
		if (recoveringLeft){
			// In recovery mode, we use max power until we reach 95% of target speed
			if(current_left_speed > (shooter_target_speed * 0.95)){
				recoveringLeft = false;
				left_color = YELLOW;
				left_power = getLeftShooterPower(shooter_target_speed);
			}
			// We're not at 95% yet, so keep recovering
			else{
				left_color = RED;
				left_power = 127;
			}
		}
		// Else in Normal mode
		else{
		// In normal mode, we use the lookup table
		// We make small adjustments (but not yet)
		// And we may move to recovery mode

		// Speed is LESS THAN 85% of target speed
		if(current_left_speed < (shooter_target_speed * 0.85)){
			recoveringLeft = true;
			left_color = RED;
			left_power = 127;
		}

		// Otherwise use canned numbers
		else {
			left_power = getLeftShooterPower(shooter_target_speed);

				if (isLeftStable(left_power)){
				purgeLeftValues();
				// Print out "Left side stable @ what power, and what speed"
				writeDebugStreamLine("Left side stable at %d speed", current_left_speed);
				writeDebugStreamLine("Left side stable at %d power", left_power);
			}

			// Now just set the colors
			// Speed is between 1% above or below target
			if(current_left_speed < (shooter_target_speed * 0.99)){
				left_color = YELLOW;
			}
			else if(current_left_speed > (shooter_target_speed * 1.01)){
				left_color = YELLOW;
			}
			// Speed is in the 2% sweet spot
			else {
				left_color = GREEN;
			}
		}
	}
		// End of Left Side Speed Control




		// Set Stoplight
		if((right_color == NONE) && (left_color == NONE)){
			setStopLight(NONE);
		}
		else if((right_color == GREEN) && (left_color == GREEN)){
			setStopLight(GREEN);
		}
		else if((right_color == RED) || (left_color == RED)){
			setStopLight(RED);
		}
		else {
			setStopLight(YELLOW);
		}

		// Control motor power
		motor[leftTopShooter] = left_power;
		motor[rightTopShooter] = right_power;
		// End of power control work.

		// Save values for next reading time.
			last_left_clicks = current_left_clicks;
			last_right_clicks = current_right_clicks;
			last_read_time = current_read_time;

			delay(20);

			print_value = (print_value + 1);
			if(print_value == 50){
				//writeDebugStreamLine("current_right_clicks: %d", current_right_clicks);
				//writeDebugStreamLine("elapsed_right_clicks: %d", elapsed_right_clicks);
				//writeDebugStreamLine("elapsed_time: %d", elapsed_time);
				//writeDebugStreamLine("current_read_time: %d", current_read_time);
				writeDebugStreamLine("************************************");
				writeDebugStreamLine("shooter_target_speed: %d", shooter_target_speed);
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

void setIntakeSpeed(int speed){
	motor[leftIntake] = speed;
	motor[rightIntake] = speed;
}
