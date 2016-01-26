#include "PIDStandardRobotPowerTable.c"
#include "StopLightControl.c"
#include "StableCheck.c"

#define ADJUST_LOCKOUT_CYCLES 35
#define PID_INTEGRAL_LIMIT 	3000

int shooter_target_speed = 0;
bool speedChange = false;
bool backOut = false;
// backOut is for returning a ball from the shooter back into the intake.
bool toggleShooterWheels = false;

bool firstRecoveryLoop = false;

task shooter_power_control(){

	// PID CONSTANTS
	float pid_Kp = .05;
	float pid_Ki = 0.012;
	float pid_Kd = -0.05;

	// create variables

	// left variables
	int last_left_clicks = 0;
	float last_Error_left = 0;
	float pid_Integral_left = 0;
	SensorValue[leftShooter] = 0;

	// right variables
	int last_right_clicks = 0;
	float last_Error_right = 0;
	float pid_Integral_right = 0;
	SensorValue[rightShooter] = 0;


	// Stabilty Checking variables, for auto shooting
	int loop_counter = 0;
	int green_counter = 0;

	// Print Loop Counter
	int print_counter = 0;

	// loop
	while(true){

		// First, are we transitioning between forward and backwards, or vise versa?
		if (toggleShooterWheels == true){
			motor[leftTopShooter] = 0;
			motor[rightTopShooter] = 0;
			delay(2000);
			toggleShooterWheels = false;
		}
		// Backout mode is simple
		if (backOut == true){
			motor[leftTopShooter] = -100;
			motor[rightTopShooter] = -100;
		}
		else if (shooter_target_speed == 0){
			motor[leftTopShooter] = 0;
			motor[rightTopShooter] = 0;
		}
		// Else we're going forward
		else
		{
			// If the speed was changed significantly, reset the Integral
			if (speedChange){
				pid_Integral_left = 0;
				pid_Integral_right = 0;
				speedChange = false;
			}

			// get speed for both sides
			// Variables for power control
			int current_right_clicks = SensorValue[rightShooter];
			int current_left_clicks = SensorValue[leftShooter];

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

			// Save Last Numbers for next loop
			last_left_clicks = current_left_clicks;
			last_right_clicks = current_right_clicks;

			// We may be in RECOVERY MODE
			if (ShooterMode == RECOVERY){

				// Reseting the integral when we're close to the target speed should
				// reduce the overshoot error on the integral, and get to the target speed quicker

				// Set motors to 100 power until we're at 90% of target speed, on one of the flywheels
				motor[leftTopShooter] = 100;
				motor[rightTopShooter] = 100;

				if(firstRecoveryLoop)
					firstRecoveryLoop = false;
				else{
					// Set motors to 100 power until we're at 90% of target speed, on one of the flywheels
					// at that point, we're in NORMAL MODE
					if 	((current_left_speed > (shooter_target_speed * .95)) ||
							 (current_right_speed > (shooter_target_speed * .95))){
						ShooterMode = NORMAL;
						writeDebugStreamLine("Exiting Recovery Mode - Reseting Integral - s.t.s = %d", shooter_target_speed);
						writeDebugStreamLine("Left - current: %d", current_left_speed);
						writeDebugStreamLine("Left - current: %d", current_right_speed);
						//pid_Integral_left = 0;
						//pid_Integral_right = 0;
					}
				}
			}
			// If we are not in RECOVERY MODE, then use PID
			else {
				/////////////////////////////////////////////////////////////////
				// DO Left Side PID
				/////////////////////////////////////////////////////////////////

				// We have the actual speed, and the current speed.

				// Calculate ERROR = Current_Speed = Actual;
				float pid_error_left = shooter_target_speed - current_left_speed;

	      // CALCULATE INTEGRAL - if Ki is not 0
	      if( pid_Ki != 0 )
	      	{
	      	// If the sign of the error changes, then reset the integral
	      	//if (sgn(pid_error_left) != (sgn(pid_Integral_left)
	      	//	pid_Integral_left = pid_error_left;
	      	// If we are inside controlable window then integrate the error
	        //else
	      	if( abs(pid_error_left) < PID_INTEGRAL_LIMIT )
	        	pid_Integral_left = pid_Integral_left + pid_error_left;
	        else
	          pid_Integral_left = 0;
	        }
	      else
	        pid_Integral_left = 0;

	      // CALCULATE DERIVATIVE
	      float pid_Derivative_left = pid_error_left - last_Error_left;

				float pid_correction_left =
					(pid_error_left * pid_Kp) +
					(pid_Integral_left * pid_Ki) +
					(pid_Derivative_left * pid_Kd);

				// SET SPEED FOR Left Flywheel
				int motor_power_left = getLeftShooterPower(shooter_target_speed) + pid_correction_left;
				if (motor_power_left > 127)
					motor_power_left = 127;
				if (motor_power_left < 0)
					motor_power_left = 0;

				motor[leftTopShooter] = motor_power_left;

				// SAVE Left Variables
				last_Error_left = pid_error_left;


				/////////////////////////////////////////////////////////////////
				// DO RIGHT SIDE PID
				/////////////////////////////////////////////////////////////////

				// We have the actual speed, and the current speed.

				// Calculate ERROR = Current_Speed = Actual;
				float pid_error_right = shooter_target_speed - current_right_speed;

	      // CALCULATE INTEGRAL - if Ki is not 0
	      if( pid_Ki != 0 )
	      	{
	      	// If the sign of the error changes, then reset the integral
	      	//if (sgn(pid_error_right) != (sgn(pid_Integral_right)
	      	//	pid_Integral_right = pid_error_right;
	      	// If we are inside controlable window then integrate the error
	        //else
	      	if( abs(pid_error_right) < PID_INTEGRAL_LIMIT )
	        	pid_Integral_right = pid_Integral_right + pid_error_right;
	        else
	          pid_Integral_right = 0;
	        }
	      else
	        pid_Integral_right = 0;

	      // CALCULATE DERIVATIVE
	      float pid_Derivative_right = pid_error_right - last_Error_right;

				float pid_correction_right =
					(pid_error_right * pid_Kp) +
					(pid_Integral_right * pid_Ki) +
					(pid_Derivative_right * pid_Kd);

				// SET SPEED FOR RIGHT Flywheel
				int motor_power_right = getRightShooterPower(shooter_target_speed)+ pid_correction_right;
				if (motor_power_right > 127)
					motor_power_right = 127;
				if (motor_power_right < 0)
					motor_power_right = 0;

				motor[rightTopShooter] = motor_power_right;
				// SAVE Right Variables
				last_Error_right = pid_error_right;


				///////////////////////////////////////////
				// DO Lights
				///////////////////////////////////////////

				left_color = RED;

				if (abs(pid_error_left) < (shooter_target_speed * .1))
					left_color = YELLOW;
				if (abs(pid_error_left) < (shooter_target_speed * .03))
					left_color = GREEN;

				right_color = RED;

				if (abs(pid_error_right) < (shooter_target_speed * .1))
					right_color = YELLOW;
				if (abs(pid_error_right) < (shooter_target_speed * .03))
					right_color = GREEN;



				// Set Stoplight
				if((right_color == NONE) && (left_color == NONE)){
					setStopLight(NONE);
				}
				else if((right_color == GREEN) && (left_color == GREEN)){
					setStopLight(GREEN);
					green_counter = green_counter + 1;
				}
				else if((right_color == RED) || (left_color == RED)){
					setStopLight(RED);
				}
				else {
					setStopLight(YELLOW);
				}
				//////////////////////////////////////////////////////////////
				// Debug info
				/////////////////////////////////////////////////////////////

				print_counter = print_counter + 1;
				if (print_counter == 10){
					writeDebugStreamLine("Left Speed: %d, Offset Power: %d", current_left_speed, pid_correction_left);
					writeDebugStreamLine("Right Speed: %d, Offset Power: %d", current_right_speed, pid_correction_right);
					print_counter = 0;
				}

				//////////////////////////////////////////////////////////////
				// Determine Shooter Mode; for autoshooting
				/////////////////////////////////////////////////////////////

				// First, detect if we just shot a ball
				// If we were ready to shoot, and the speed is way off ( <85% target speed on both sides
				// Then we think we just fired a ball, this will reset the mode to "RECOVERY"
				if ((ShooterMode == READY_TO_SHOOT)
						&& (current_left_speed < (.88 * shooter_target_speed))
						&& (current_right_speed < (.88 * shooter_target_speed))){
					ballFireDetected();
					firstRecoveryLoop = true;
					loop_counter = 0;
					green_counter = 0;

					// reset integrals after firing:
					pid_Integral_left = 0;
					pid_Integral_right = 0;
				}
				// Else we are not ready to shoot.  Increment to loop counters, and green counts appropriately
				// If there's enough Greens out of the last X times through the loop; then set the ShooterMode
				// to READY_TO_SHOOT.   This is stay, until Recovery mode.
				else {
					loop_counter = loop_counter + 1;
					//Don't let the counts get too high!!!
					if (loop_counter > 30){
						green_counter = 0;
						loop_counter = 0;
					}
					if (isShooterReady(green_counter,loop_counter)){
						ShooterMode = READY_TO_SHOOT;
					}
				}

			} // End Else (NORMAL MODE)
		} // End Else (Going Forward)
		delay(20);
	} // End While loop
}


void set_shooter_targets(int speed){
	// If we are changing to a higher speed (> 100 more speed)
	// Then jump into recovery mode
	if ((speed - 100) > shooter_target_speed){
		ShooterMode = RECOVERY;
		firstRecoveryLoop = true;
	}
	shooter_target_speed = speed;
	speedChange = true;
	writeDebugStreamLine("Shooter Target Speed: %d", shooter_target_speed);
}

void adjust_shooter_targets(int adjust_speed){
	// For now, adjust value a bit, and print a debug statement
	shooter_target_speed = shooter_target_speed + adjust_speed;
	//speedChange = true;
	writeDebugStreamLine("Shooter Target Speed: %d", shooter_target_speed);
}
