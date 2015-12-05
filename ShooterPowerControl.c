#include "Filter.c"
#include "MockRobotPowerTable.c"
#include "StopLightControl.c"

int shooter_target_speed = 0;

// Global Variables for shooter control
// These are set by the joystick methods

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


		// Stoplight color controls
		int left_color = NONE;
		int right_color = NONE;

		// Do power control with filtered values;

		if(shooter_target_speed == 0){
			right_color = NONE;
			right_power = 0;
		}
		// Speed is more than 25% below target
		else if(current_right_speed < (shooter_target_speed * 0.75)){
			right_color = RED;
			right_power = 127;
		}
		// Speed is more than 25% above target
		else if(current_right_speed > (shooter_target_speed * 1.25)){
			right_color = RED;
			right_power = getRightShooterPower(shooter_target_speed);
		}
		// Speed is between 10% and 1% below target
		else if(current_right_speed < (shooter_target_speed * 0.99)){
			right_color = YELLOW;
			right_power = right_power + 1;
		}
		// Speed is between 1% and 10% above target
		else if(current_right_speed > (shooter_target_speed * 1.01)){
			right_color = YELLOW;
			right_power = right_power - 1;
		}
		// Speed is in the 2% sweet spot
		else {
			right_color = GREEN;
		}

		// Motors are stopped
		if(shooter_target_speed == 0){
			left_color = NONE;
			left_power = 0;
		}
		// Speed is MORE THAN 25% BELOW target
		else if(current_left_speed < (shooter_target_speed * 0.75)){
			left_color = RED;
			left_power = 127;
		}
		// Speed is MORE THAN 25% ABOVE target
		else if(current_left_speed > (shooter_target_speed * 1.25)){
			left_color = RED;
			left_power = getLeftShooterPower(shooter_target_speed);
		}
		// Speed is 10% BELOW target
		else if(current_left_speed < (shooter_target_speed * 0.99)){
			left_color = YELLOW;
			left_power = left_power + 1;
		}
		// Speed is 10% ABOVE target
		else if(current_left_speed > (shooter_target_speed * 1.01)){
			left_color = YELLOW;
			left_power = left_power - 1;
		}
		// Speed is within 2% sweet spot
		else {
			left_color = GREEN;
		}


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

			delay(100);

			print_value = (print_value + 1);
			if(print_value == 10){
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

void setIntakeSpeed(int speed){
	motor[leftIntake] = speed;
	motor[rightIntake] = speed;
}
