
#include "Filter.c"
#include "RealRobotPowerTable.c"
#include "StopLightControl.c"
#include "StableCheck.c"

#define ADJUST_LOCKOUT_CYCLES 40

int shooter_target_speed = 0;
int power_offset = 0;
bool backOut = false;

// backOut is for returning a ball from the shooter back into the intake.
bool toggleShooterWheels = false;

// Global Variables for shooter control
// These are set by the joystick methods


task shooter_power_control()
{

	int RangePower = 0;

	while(true)
	{
		if (backOut == true){
			motor[leftTopShooter] = -100;
			motor[rightTopShooter] = -100;
		}

		else{

		// Set the range_power by Shooter Target Speed
		// If the Shooter Target Speed is 0, Stop
		if (shooter_target_speed == 0){
			RangePower = 0;
		}
			// Else if STS is 910 (long range) then set RangePower to power high
		else if (shooter_target_speed == 910){
			RangePower = 68;
		}
			// Else if STS is 780, set RangePower to mid
		else if (shooter_target_speed == 780){
			RangePower = 38;
		}
			// Else if STS is 620, set to short
		else if (shooter_target_speed == 620){
			RangePower = 32;
		}
			// Else something is wrong, set to 0
		else {
			RangePower = 0;
		}


			// Control motor power
			motor[leftTopShooter] = RangePower + power_offset;
			motor[rightTopShooter] = RangePower + power_offset;
			// End of power control work.

			delay(20);
		}
	}
}


void set_shooter_targets(int speed){
	// For now, set value and print a debug statement
	shooter_target_speed = speed;
}

void adjust_shooter_targets(int adjustment){
	if (adjustment == 10){
		power_offset = power_offset + 1;
	}
	else if (adjustment == -10){
		power_offset = power_offset - 1;
	}
}
