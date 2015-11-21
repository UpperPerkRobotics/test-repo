#pragma config(Sensor, dgtl1,  greenLED,       sensorLEDtoVCC)
#pragma config(Sensor, dgtl4,  LeftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl11, RightEncoder,   sensorQuadEncoder)
#pragma config(Motor,  port8,           Shooter8,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           Shooter9,      tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#define JOYSTICK_AVAIL false

int shooter_target_speed = 0;

task Shooting()
{

	int last_clicks_left = 0;
	int last_clicks_right = 0;

	while(true)
	{
		motor[Shooter8] = shooter_target_speed;
		motor[Shooter9] = shooter_target_speed;
		if (shooter_target_speed > 80)
		{
			SensorValue[dgtl1] = 1;
		}
		else
		{
			SensorValue[dgtl1] = 0;
		}
		//get current
		int current_right_clicks = SensorValue[RightEncoder];
		int current_left_clicks = SensorValue[LeftEncoder];
		//calculate elapsed
		int elapsed_right_clicks = current_right_clicks - last_clicks_right;
		int elapsed_left_clicks = current_left_clicks - last_clicks_left;
		//print
		writeDebugStreamLine("elapsed_right_clicks: %d", elapsed_right_clicks);
		writeDebugStreamLine("elapese_left_clicks: %d", elapsed_left_clicks);
		//save current to last
		writeDebugStreamLine("shooter_target_speed: %d", shooter_target_speed);
		last_clicks_left = current_left_clicks;
		last_clicks_right = current_right_clicks;
		delay(100);
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

task Controls()
{
	while(true){
		if (!JOYSTICK_AVAIL){
			set_motor_target_speed(65);
			delay(10000);
		}
			// Check each button and do actions
		else if(vexRT[Btn8U] == 1){
			// Set motor target speed (Far), Channel 8, Button U
			set_motor_target_speed(85);
			delay(500);
		}
		else if(vexRT[Btn8R] == 1){
			// Set motor target speed (Medium), Channel 8, Button R
			set_motor_target_speed(60);
			delay(500);
		}
		else if(vexRT[Btn8D] == 1){
			// Set motor target speed (Short), Channel 8, Button D
			set_motor_target_speed(40);
			delay(500);
		}
		else if(vexRT[Btn6U] == 1){
			// Adjust motor target speed (5 up), Channel 6, Button U
			adjust_target_speed(3);
			delay(250);
		}
		else if(vexRT[Btn6D] == 1){
			// Adjust motor target speed (5 down), Channel 6, Button D
			adjust_target_speed(-3);
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
task main()
{
	startTask(Shooting);
	startTask(Controls);
	while(true)
	{
		delay(1000);
}
}
