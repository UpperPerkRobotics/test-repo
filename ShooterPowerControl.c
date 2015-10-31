#pragma config(Sensor, dgtl4,  leftShooter,    sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  rightShooter,   sensorQuadEncoder)
#pragma config(Motor,  port2,           leftDrive,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightDrive,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           leftTopShooter, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           rightTopShooter, tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int shooter_target_speed = 0;

task shooter_power_control()
{
	int last_right_clicks = 0;
	int last_left_clicks = 0;
	int last_read_time = -10;

	int print_value = 0;

	while(true)
	{


		int current_right_clicks = SensorValue[rightShooter];
		int current_left_clicks = SensorValue[leftShooter];
		int current_read_time = nPgmTime;

		int elapsed_right_clicks = current_right_clicks - last_right_clicks;
		int elapsed_left_clicks = current_left_clicks - last_left_clicks;
		int elapsed_time = current_read_time - last_read_time;

		int current_right_speed = elapsed_right_clicks * 20;
		int current_left_speed = elapsed_left_clicks * 20;
		//int current_right_speed = (elapsed_right_clicks * 20)/elapsed_time;
		//int current_left_speed = (elapsed_left_clicks * 20)/elapsed_time;


		// right side power control
			/*
			if (shooter_target_speed == 0)
			{
				motor[rightTopShooter] = 0;
			}
			else if ((current_right_speed + 10) < shooter_target_speed)
			{
				motor[rightTopShooter] = 127;
			}
			else if (shooter_target_speed > current_right_speed)
			{
				motor[rightTopShooter] = (motor[rightTopShooter] + 1);
			}
			else if (shooter_target_speed < current_right_speed)
			{
				motor[rightTopShooter] = (motor[rightTopShooter]  - 1);
			}
			*/
			if (shooter_target_speed == 0)
			{
				motor[rightTopShooter] = 0;
			}
			else
			{
				int right_delta = shooter_target_speed - current_right_speed;
				if ((motor[rightTopShooter] + right_delta) > 0){
					motor[rightTopShooter] = motor[rightTopShooter] + right_delta;
				}
				else
			  {
		      motor[rightTopShooter] = 0;
			  }
		}
			last_right_clicks = current_right_clicks;

		// left side power control
			/*
			if (shooter_target_speed == 0)
			{
				motor[leftTopShooter] = 0;
			}
			else if ((current_left_speed + 10) < shooter_target_speed)
			{
				motor[leftTopShooter] = 127;
			}
			else if (shooter_target_speed > current_left_speed)
			{
				motor[leftTopShooter] = (motor[leftTopShooter] + 1);
			}
			else if (shooter_target_speed < current_left_speed)
			{
				motor[leftTopShooter] = (motor[leftTopShooter]  - 1);
			}
			*/

			if (shooter_target_speed == 0)
			{
				motor[leftTopShooter] = 0;
			}
			else
			{
				int left_delta = shooter_target_speed - current_left_speed;
				if ((motor[leftTopShooter] + left_delta) > 0){
					motor[leftTopShooter] = motor[leftTopShooter] + left_delta;
				}
				else
			  {
		      motor[leftTopShooter] = 0;
			  }
		}

			last_left_clicks = current_left_clicks;
			last_read_time = current_read_time;

			delay(500);

			print_value = (print_value + 1);
			if(print_value == 1){
				//writeDebugStreamLine("current_right_clicks: %d", current_right_clicks);
				writeDebugStreamLine("current_right_speed: %d", current_right_speed);
				//writeDebugStreamLine("elapsed_right_clicks: %d", elapsed_right_clicks);
				//writeDebugStreamLine("elapsed_time: %d", elapsed_time);
				//writeDebugStreamLine("current_read_time: %d", current_read_time);
				writeDebugStreamLine("shooter_target_speed: %d", shooter_target_speed);
				writeDebugStreamLine("right shooter power: %d", motor[rightTopShooter]);

				print_value = 0;
			}

	}
}


void set_motor_target_speed(int speed){
	// For now, set value and print a debug statement
	shooter_target_speed = speed;
	writeDebugStreamLine("Shooter Target Speed: %d", shooter_target_speed);
}

void adjust_target_speed(int adjustment){
	// For now, adjust value a bit, and print a debug statement
	shooter_target_speed = shooter_target_speed + adjustment;
	writeDebugStreamLine("Shooter Target Speed: %d", shooter_target_speed);
}

// Read Buttons to see if any are pushed
task controllerPolling(){
	while(true){
		// Check each button and do actions
		if(vexRT[Btn8U] == 1){
			// Set motor target speed (Far), Channel 8, Button U
			set_motor_target_speed(127);
			delay(500);
		}
		else if(vexRT[Btn8R] == 1){
			// Set motor target speed (Medium), Channel 8, Button R
			set_motor_target_speed(80);
			delay(500);
		}
		else if(vexRT[Btn8D] == 1){
			// Set motor target speed (Short), Channel 8, Button D
			set_motor_target_speed(30);
			delay(500);
		}
		else if(vexRT[Btn6U] == 1){
			// Adjust motor target speed (5 up), Channel 6, Button U
			adjust_target_speed(5);
			delay(250);
		}
		else if(vexRT[Btn6D] == 1){
			// Adjust motor target speed (5 down), Channel 6, Button D
			adjust_target_speed(-5);
			delay(250);
		}
		else if(vexRT[Btn8L] == 1){
			// Stop all motor speed (0), Channel 8, Button L
			set_motor_target_speed(0);
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
