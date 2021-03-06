#include "Filter.c"
#include "RealRobotPowerTable.c"
#include "StopLightControl.c"
#include "StableCheck.c"

#define ADJUST_LOCKOUT_CYCLES 35

int shooter_target_speed = 0;
bool speedChange = false;
bool backOut = false;
// backOut is for returning a ball from the shooter back into the intake.
bool toggleShooterWheels = false;

// Global Variables for shooter control
// These are set by the joystick methods

task shooter_power_control(){

	int rightPowerOffset = 0;
	int leftPowerOffset = 0;

	bool recoveringRight = false;
	bool recoveringLeft = false;


	int last_right_clicks = 0;
	int last_left_clicks = 0;
	int last_read_time = -10;

	int left_power = 0;
	int right_power = 0;

	int left_adjust_lockout = 0;
	int right_adjust_lockout = 0;

	int loop_counter = 0;
	int green_counter = 0;

	while(true)
	{
		if (toggleShooterWheels == true){
			motor[leftTopShooter] = 0;
			motor[rightTopShooter] = 0;
			delay(2000);
			toggleShooterWheels = false;
		}
		// Backout mode has highest priority
		if (backOut == true){
			motor[leftTopShooter] = -100;
			motor[rightTopShooter] = -100;
		}
		// Otherwise, normal mode with target speeds
		else
		{
			loop_counter = loop_counter + 1;
			//Don't let the counts get too high!!!
			if (loop_counter > 30){
				green_counter = 0;
				loop_counter = 0;
			}

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


			//Using lockout timer to not over-adjust
			//Every cycle lower the lockout timer; only allow changes if timer is 0;

			if (left_adjust_lockout > 0)
				left_adjust_lockout = left_adjust_lockout - 1;

			if (right_adjust_lockout > 0)
				right_adjust_lockout = right_adjust_lockout - 1;

			// Do power control with filtered values;
			if(shooter_target_speed == 0){
				right_color = NONE;
				right_power = 0;

				left_color = NONE;
				left_power = 0;

				ShooterMode = STOPPED;
			}

			// else shooter target speed > 0
			else{
				// Right Side Speed Control
				// Right Side is in recovery mode
				if (recoveringRight){
					// In recovery mode, we use max power until we reach 85% of target speed
					if(current_right_speed > (shooter_target_speed * 0.85)){
						recoveringRight = false;
						right_adjust_lockout = ADJUST_LOCKOUT_CYCLES ;
						right_color = YELLOW;
						right_power = getRightShooterPower(shooter_target_speed) + rightPowerOffset;

						// ending recovery, clear counters
						green_counter = 0;
						loop_counter = 0;

						writeDebugStreamLine("Right Side Now NORMAL Mode - Adjusted Power: %d (%d Offset)", right_power, rightPowerOffset);
					}
					// We're not at 95% yet, so keep recovering
					else{
						right_color = RED;
						right_power = 80;
					}
				}
				// Else in Normal mode
				else{
				// In normal mode, we use the lookup table
				// We make small adjustments (but not yet)
				// And we may move to recovery mode

				// Speed is LESS THAN 85% of target speed
					if(current_right_speed < (shooter_target_speed * 0.8)){
						writeDebugStreamLine("Right Side Now **** RECOVERY MODE ***");
						recoveringRight = true;
						right_color = RED;
						right_power = 80;
						rightHitStable = false;
					}
					// Otherwise use canned numbers with correcting offset
					else {

						// IF stable, we may adjust the offset
						int rightStableCheckResult = isRightStable(current_right_speed);
						if (rightStableCheckResult > 0){
							purgeRightValues();
							// Print out "Right side stable @ what power, and what speed"
							writeDebugStreamLine("Right side stable %d speed (REAL)", current_right_speed);
							current_right_speed = rightStableCheckResult;
							writeDebugStreamLine("Right side stable at %d speed (FORECAST)", current_right_speed);

							// Speed is less than 90% target, add POWER!!!
							if(current_right_speed < (shooter_target_speed * 0.9)){
								// PowerOffset should never go over 30...
								// If so, something's wrong
								if ((rightPowerOffset < 30) && (right_adjust_lockout == 0)){
									rightPowerOffset = rightPowerOffset + 3;
									right_adjust_lockout = ADJUST_LOCKOUT_CYCLES;
									writeDebugStreamLine("Right Side Offset Adjust +3 - Adjusted Power: %d (%d Offset)", right_power, rightPowerOffset);
								}
							}
							else if(current_right_speed < (shooter_target_speed - 30)){
								// PowerOffset should never go over 30...
								// If so, something's wrong
								if ((rightPowerOffset < 30) && (right_adjust_lockout == 0)){
									rightPowerOffset = rightPowerOffset + 2;
									right_adjust_lockout = ADJUST_LOCKOUT_CYCLES;
									writeDebugStreamLine("Right Side Offset Adjust +2 - Adjusted Power: %d (%d Offset)", right_power, rightPowerOffset);
								}
							}
							else if(current_right_speed < (shooter_target_speed - 10)){
								// PowerOffset should never go over 30...
								// If so, something's wrong
								if ((rightPowerOffset < 30) && (right_adjust_lockout == 0)){
									rightPowerOffset = rightPowerOffset + 1;
									right_adjust_lockout = ADJUST_LOCKOUT_CYCLES;
									writeDebugStreamLine("Right Side Offset Adjust +1 - Adjusted Power: %d (%d Offset)", right_power, rightPowerOffset);
								}
							}
							else if(current_right_speed > (shooter_target_speed * 1.1)){
								if ((rightPowerOffset > -30) && (right_adjust_lockout == 0)){
									rightPowerOffset = rightPowerOffset - 3;
									right_adjust_lockout = ADJUST_LOCKOUT_CYCLES;
									writeDebugStreamLine("Right Side Offset Adjust - 3 - Adjusted Power: %d (%d Offset)", right_power, rightPowerOffset);
								}
							}
							else if(current_right_speed > (shooter_target_speed + 40)){
								if ((rightPowerOffset > -30) && (right_adjust_lockout == 0)){
									rightPowerOffset = rightPowerOffset - 2;
									right_adjust_lockout = ADJUST_LOCKOUT_CYCLES;
									writeDebugStreamLine("Right Side Offset Adjust - 2 - Adjusted Power: %d (%d Offset)", right_power, rightPowerOffset);
								}
							}
							else if(current_right_speed > (shooter_target_speed + 20)){
								if ((rightPowerOffset > -30) && (right_adjust_lockout == 0)){
									rightPowerOffset = rightPowerOffset - 1;
									right_adjust_lockout = ADJUST_LOCKOUT_CYCLES;
									writeDebugStreamLine("Right Side Offset Adjust -1 - Adjusted Power: %d (%d Offset)", right_power, rightPowerOffset);
								}
							}
							// Speed is in the 4% sweet spot
							else {
								right_color = GREEN;
								rightHitStable = true;
							}
						} // end is stable

						// Now set the power level, and color
						right_power = getRightShooterPower(shooter_target_speed) + rightPowerOffset;
						right_color = YELLOW;
						if (((current_right_speed > (shooter_target_speed - 30)) &&
								(current_right_speed < (shooter_target_speed + 40))) || rightHitStable) {
									right_color = GREEN;
						}

					} // end else (use canned numbers)
				} // end else (normal mode)
			// End of Right side Speed Control

			// Left Side Speed Control
				// Left Side is in recovery mode
				if (recoveringLeft){
					// In recovery mode, we use max power until we reach 85% of target speed
					if(current_left_speed > (shooter_target_speed * 0.85)){
						recoveringLeft = false;
						left_adjust_lockout = ADJUST_LOCKOUT_CYCLES ;
						left_color = YELLOW;
						left_power = getLeftShooterPower(shooter_target_speed) + leftPowerOffset;

						// ending recovery, clear counters
						green_counter = 0;
						loop_counter = 0;

						writeDebugStreamLine("Left Side Now NORMAL Mode - Adjusted Power: %d (%d Offset)", left_power, leftPowerOffset);
					}
					// We're not at 95% yet, so keep recovering
					else{
						left_color = RED;
						left_power = 80;
					}
				}
				// Else in Normal mode
				else{
				// In normal mode, we use the lookup table
				// We make small adjustments (offset)
				// And we may move to recovery mode

				// Speed is LESS THAN 80% of target speed
					if(current_left_speed < (shooter_target_speed * 0.8)){
						writeDebugStreamLine("Left Side Now *** RECOVERY MODE ****");
						recoveringLeft = true;
						left_color = RED;
						left_power = 80;
						leftHitStable = false;
					}

					// Otherwise use canned numbers and Offset
					else {


						// IF stable, we may adjust the offset
						int leftStableCheckResult = isLeftStable(current_right_speed);
						if (leftStableCheckResult > 0){
							purgeLeftValues();
							// Print out "Left side stable @ what power, and what speed"
							writeDebugStreamLine("Left side stable %d speed (REAL)", current_left_speed);
							current_left_speed = leftStableCheckResult;
							writeDebugStreamLine("Left side stable at %d speed (FORECAST)", current_left_speed);


							// Speed is less than 90% of target, add POWER!!!
							if(current_left_speed < (shooter_target_speed * 0.9)){
								if((leftPowerOffset < 30) && (left_adjust_lockout == 0)){
									leftPowerOffset = leftPowerOffset + 3;
									left_adjust_lockout = ADJUST_LOCKOUT_CYCLES;
									writeDebugStreamLine("Left Side Offset Adjust +3 - Adjusted Power: %d (%d Offset)", left_power, leftPowerOffset);
								}
							}
							else if(current_left_speed < (shooter_target_speed - 30)){
								if((leftPowerOffset < 30) && (left_adjust_lockout == 0)){
									leftPowerOffset = leftPowerOffset + 2;
									left_adjust_lockout = ADJUST_LOCKOUT_CYCLES;
									writeDebugStreamLine("Left Side Offset Adjust +2 - Adjusted Power: %d (%d Offset)", left_power, leftPowerOffset);
								}
							}
							else if(current_left_speed < (shooter_target_speed - 10)){
								if((leftPowerOffset < 30) && (left_adjust_lockout == 0)){
									leftPowerOffset = leftPowerOffset + 1;
									left_adjust_lockout = ADJUST_LOCKOUT_CYCLES;
									writeDebugStreamLine("Left Side Offset Adjust +1 - Adjusted Power: %d (%d Offset)", left_power, leftPowerOffset);
								}
							}
							else if(current_left_speed > (shooter_target_speed * 1.1)){
								if((leftPowerOffset > -30) && (right_adjust_lockout == 0)){
									leftPowerOffset = leftPowerOffset - 3;
									left_adjust_lockout = ADJUST_LOCKOUT_CYCLES;
									writeDebugStreamLine("Left Side Offset Adjust -3 - Adjusted Power: %d (%d Offset)", left_power, leftPowerOffset);
								}
							}
							else if(current_left_speed > (shooter_target_speed + 40)){
								if((leftPowerOffset > -30) && (right_adjust_lockout == 0)){
									leftPowerOffset = leftPowerOffset - 2;
									left_adjust_lockout = ADJUST_LOCKOUT_CYCLES;
									writeDebugStreamLine("Left Side Offset Adjust -2 - Adjusted Power: %d (%d Offset)", left_power, leftPowerOffset);
								}
							}
							else if(current_left_speed > (shooter_target_speed + 20)){
								if((leftPowerOffset > -30) && (right_adjust_lockout == 0)){
									leftPowerOffset = leftPowerOffset - 1;
									left_adjust_lockout = ADJUST_LOCKOUT_CYCLES;
									writeDebugStreamLine("Left Side Offset Adjust -1 - Adjusted Power: %d (%d Offset)", left_power, leftPowerOffset);
								}
							}
							// Speed is in the 4% sweet spot
							else {
								left_color = GREEN;
								leftHitStable = true;
							}
						} // end is stable
						// Now set the power level, and color
						left_power = getLeftShooterPower(shooter_target_speed) + leftPowerOffset;
						left_color = YELLOW;
						if (((current_left_speed > (shooter_target_speed - 30)) &&
								(current_left_speed < (shooter_target_speed + 40))) || leftHitStable){
									left_color = GREEN;
						}
					} // end "else use canned numbers"
				} // end "else in normal mode"
			// End of Left Side Speed Control
			} // End "Else shooter Target speed > 0

			// Set Stoplight
			if((right_color == NONE) && (left_color == NONE)){
				setStopLight(NONE);
			}
			else if((right_color == GREEN) && (left_color == GREEN)){
				setStopLight(GREEN);
				green_counter = green_counter + 1;
				if (isShooterReady(green_counter,loop_counter)){
					ShooterMode = READY_TO_SHOOT;
				}
				else{
					ShooterMode = NORMAL;
				}
			}
			else if((right_color == RED) || (left_color == RED)){
				// RED LIGHT = RECOVERY MODE!!!
				setStopLight(RED);
				ShooterMode = RECOVERY;
			}
			else {
				setStopLight(YELLOW);
				if (isShooterReady(green_counter,loop_counter)){
					ShooterMode = READY_TO_SHOOT;
				}
				else{
					ShooterMode = NORMAL;
				}
			}

			// The speed was changed, print the new target powers
			if (speedChange){
				speedChange = false;
				writeDebugStreamLine("Left Side New - Adjusted Power: %d (%d Offset)", left_power, leftPowerOffset);
				writeDebugStreamLine("Right Side New - Adjusted Power: %d (%d Offset)", right_power, rightPowerOffset);
				leftHitStable = false;
				rightHitStable = false;
			}

			// Control motor power
			motor[leftTopShooter] = left_power;
			motor[rightTopShooter] = right_power;
			// End of power control work.

			// Save values for next reading time.
			last_left_clicks = current_left_clicks;
			last_right_clicks = current_right_clicks;
			last_read_time = current_read_time;

		// End of Target-Speed-Controlled mode (The NON-Backout Mode)
		}

		delay(20);
	}
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
