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
	float pid_Kp = 0.05;
	float pid_Ki = 0.0115;
	float pid_Kd = 0;

	// create variables

	// left variables
	int last_left_clicks = 0;
	float last_Error = 0;
	float pid_Integral = 0;
	SensorValue[leftShooter] = 0;

	// right variables
	int last_right_clicks = 0;
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
				pid_Integral = 0;
				speedChange = false;
			}

			// get speed for both sides
			// Variables for power control
			// int current_right_clicks = SensorValue[rightShooter];
			// Sensor's backwords
			int current_left_clicks = SensorValue[leftShooter];

			// current raw speed
			// int elapsed_right_clicks = current_right_clicks - last_right_clicks;
			int elapsed_left_clicks = current_left_clicks - last_left_clicks;
			// int elapsed_time = current_read_time - last_read_time;

			int elapsed_clicks = elapsed_left_clicks * 1;

			// filtered speed
			int current_speed = elapsed_clicks * 5;

			// Stoplight color controls
			int color = NONE;
			int right_color = NONE;

			// Save Last Numbers for next loop
			last_left_clicks = current_left_clicks;

			// We may be in RECOVERY MODE
			if (ShooterMode == RECOVERY){

				// Reseting the integral when we're close to the target speed should
				// reduce the overshoot error on the integral, and get to the target speed quicker

				// Set motors to 100 power until we're at 90% of target speed, on one of the flywheels
				motor[leftTopShooter] = 127;
			  motor[rightTopShooter] = 127;

				if(firstRecoveryLoop)
					firstRecoveryLoop = false;
				else{
					// Set motors to 100 power until we're at 90% of target speed, on one of the flywheels
					// at that point, we're in NORMAL MODE
					if 	(current_speed > (shooter_target_speed - 45)){
						ShooterMode = NORMAL;
						writeDebugStreamLine("Exiting Recovery Mode - Reseting Integral - s.t.s = %d", shooter_target_speed);
						writeDebugStreamLine("Left - current: %d", current_speed);
						writeDebugStreamLine("Right - current: %d", current_speed);
						pid_Integral = 0;
					}
				}

				//////////////////////////////////////////////////////////////
				// Debug info
				/////////////////////////////////////////////////////////////

				print_counter = print_counter + 1;
				if (print_counter == 10){
					writeDebugStreamLine("Recovery Mode Speed: %d", current_speed);
					print_counter = 0;
				}
			}
			// If we are not in RECOVERY MODE, then use PID
			else {
				/////////////////////////////////////////////////////////////////
				// DO PID
				/////////////////////////////////////////////////////////////////

				// We have the actual speed, and the current speed.

				// Calculate ERROR = Current_Speed = Actual;
				float pid_error = shooter_target_speed - current_speed;

	      // CALCULATE INTEGRAL - if Ki is not 0
	      if( pid_Ki != 0 )
	      	{
	      	// If the sign of the error changes, then reset the integral
	      	//if (sgn(pid_error_left) != (sgn(pid_Integral_left)
	      	//	pid_Integral_left = pid_error_left;
	      	// If we are inside controlable window then integrate the error
	        //else
	      	if( abs(pid_error) < PID_INTEGRAL_LIMIT )
	        	pid_Integral = pid_Integral + pid_error;
	        else
	          pid_Integral = 0;
	        }
	      else
	        pid_Integral = 0;

	      // CALCULATE DERIVATIVE
	      float pid_Derivative = pid_error - last_Error;

				float pid_correction =
					(pid_error * pid_Kp) +
					(pid_Integral * pid_Ki) +
					(pid_Derivative * pid_Kd);

				// SET SPEED FOR Flywheel
				int motor_power = getLeftShooterPower(shooter_target_speed) + pid_correction;
				if (motor_power > 127)
					motor_power = 127;
				if (motor_power < 0)
					motor_power = 0;

				motor[leftTopShooter] = motor_power;
				motor[rightTopShooter] = motor_power;

				// SAVE Left Variables
				last_Error = pid_error;


				///////////////////////////////////////////
				// DO Lights
				///////////////////////////////////////////

				color = RED;

				if (abs(pid_error) < (shooter_target_speed * .1))
					color = YELLOW;
				if (abs(pid_error) < (shooter_target_speed * .03))
					color = GREEN;


				// Set Stoplight
				if(ShooterMode == READY_TO_SHOOT){
					setStopLight(GREEN);
				}
				else if(color == NONE){
					setStopLight(NONE);
				}
				else if(color == GREEN){
					setStopLight(GREEN);
					green_counter = green_counter + 1;
				}
				else if(color == RED){
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
					writeDebugStreamLine("Speed: %d, Offset Power: %d", current_speed, pid_correction);
					print_counter = 0;
				}

				//////////////////////////////////////////////////////////////
				// Determine Shooter Mode; for autoshooting
				/////////////////////////////////////////////////////////////

				// First, detect if we just shot a ball
				// If we were ready to shoot, and the speed is way off ( <85% target speed on both sides
				// Then we think we just fired a ball, this will reset the mode to "RECOVERY"
				if ((ShooterMode == READY_TO_SHOOT)
						&& (current_speed < (.9 * shooter_target_speed))){
					ballFireDetected();
					firstRecoveryLoop = true;
					loop_counter = 0;
					green_counter = 0;

					// reset integrals after firing:
					pid_Integral = 0;
				}
				// Else we are not ready to shoot.  Increment to loop counters, and green counts appropriately
				// If there's enough Greens out of the last X times through the loop; then set the ShooterMode
				// to READY_TO_SHOOT.   This is stay, until Recovery mode.
				else {
					loop_counter = loop_counter + 1;
					//Don't let the counts get too high!!!
					if (loop_counter > 16){
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
