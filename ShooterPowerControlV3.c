#include "Filter.c"
#include "RealRobotPowerTable.c"
#include "StopLightControl.c"
#include "StableCheck.c"

int shooter_target_speed = 0;
bool speedChange = false;

// Global Variables for shooter control
// These are set by the joystick methods

task shooter_power_control(){

	bool recoveringRight = false;
	bool recoveringLeft = false;

	int last_right_clicks = 0;
	int last_left_clicks = 0;
	int last_read_time = -10;

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

			left_color = NONE;
			left_power = 0;
		}
		// Otherwise, target speed is > 0;
		else {

			// Right Side Speed Control
			// Right Side is in recovery mode
			if (recoveringRight){
				// In recovery mode, we use max power until we reach 95% of target speed
				if(current_right_speed > (shooter_target_speed * 0.95)){
					recoveringRight = false;
					right_color = YELLOW;
					right_power = getRightShooterPower(shooter_target_speed);
					writeDebugStreamLine("Right Side Now NORMAL Mode - Fixed Power: %d", right_power);
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
					writeDebugStreamLine("Right Side ***** RECOVERY MODE ****** ");
					recoveringRight = true;
					right_color = RED;
					right_power = 127;
				}

				// Otherwise use canned numbers
				else {
					right_power = getRightShooterPower(shooter_target_speed);

					if (isRightStable(current_right_speed)){
						purgeRightValues();
						// Print out "Right side stable @ what power, and what speed"
						writeDebugStreamLine("Right side stable at %d speed", current_right_speed);
					}

					// Now just set the colors
					// Speed is between 1% above or below target
					if(current_right_speed < (shooter_target_speed * 0.98)){
						right_color = YELLOW;
					}
					else if(current_right_speed > (shooter_target_speed * 1.02)){
						right_color = YELLOW;
					}
					// Speed is in the 4% sweet spot
					else {
						right_color = GREEN;
					}
				} // end use cannded numbers
			} // end "else normal mode"
			// End of Right side Speed Control

			// Left Side Speed Control
			// Left Side is in recovery mode
			if (recoveringLeft){
				// In recovery mode, we use max power until we reach 95% of target speed
				if(current_left_speed > (shooter_target_speed * 0.95)){
					recoveringLeft = false;
					left_color = YELLOW;
					left_power = getLeftShooterPower(shooter_target_speed);
					writeDebugStreamLine("Left Side Now NORMAL Mode - Fixed Power: %d", left_power);
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
					writeDebugStreamLine("Left Side **** RECOVERY MODE *****");
					recoveringLeft = true;
					left_color = RED;
					left_power = 127;
				}

				// Otherwise use canned numbers
				else {
					left_power = getLeftShooterPower(shooter_target_speed);

					if (isLeftStable(current_left_speed)){
						purgeLeftValues();
						// Print out "Right side stable @ what power, and what speed"
						writeDebugStreamLine("Left side stable at %d speed", current_left_speed);
					}

					// Now just set the colors
					// Speed is between 1% above or below target
					if(current_left_speed < (shooter_target_speed * 0.98)){
						left_color = YELLOW;
					}
					else if(current_left_speed > (shooter_target_speed * 1.02)){
						left_color = YELLOW;
					}
					// Speed is in the 4% sweet spot
					else {
						left_color = GREEN;
					}
				} // end "else use canned numbers"
			} // end "else normal mode"
			// End of Left Side Speed Control
		} // end "else target speed > 0"



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

		// The speed was changed, print the new target powers
		if (speedChange){
			speedChange = false;
			writeDebugStreamLine("Left Side New - Fixed Power: %d", left_power);
			writeDebugStreamLine("Right Side New - Fixed Power: %d", right_power);
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

	} // end while
}


void set_shooter_targets(int speed){
	// For now, set value and print a debug statement
	shooter_target_speed = speed;
	speedChange = true;
	writeDebugStreamLine("Shooter Target Speed: %d", shooter_target_speed);
}

void adjust_shooter_targets(int adjust_speed){
	// For now, adjust value a bit, and print a debug statement
	shooter_target_speed = shooter_target_speed + adjust_speed;
	speedChange = true;
	writeDebugStreamLine("Shooter Target Speed: %d", shooter_target_speed);
}

void setIntakeSpeed(int speed){
	motor[leftIntake] = speed;
	motor[rightIntake] = speed;
}
