#pragma config(Sensor, dgtl4,  leftShooter,    sensorQuadEncoder)
#pragma config(Sensor, dgtl6,  rightShooter,   sensorQuadEncoder)
#pragma config(Motor,  port2,           leftDrive,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rightDrive,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           leftTopShooter, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           rightTopShooter, tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//


task shooter_power_control()
{


	int last_left_clicks = 0;
	int print_value = 0;
	SensorValue[leftShooter] = 0;
	int current_left_clicks = 0;

	while(true)
	{

	  motor[leftTopShooter] = 25;
		current_left_clicks = SensorValue[leftShooter];

		int current_left_speed = current_left_clicks - last_left_clicks;
		last_left_clicks = current_left_clicks;

		print_value = (print_value + 1);
		if(print_value == 1){
			//writeDebugStreamLine("current_right_clicks: %d", current_right_clicks);
			writeDebugStreamLine("current_right_speed: %d", current_left_speed);
			//writeDebugStreamLine("elapsed_right_clicks: %d", elapsed_right_clicks);
			//writeDebugStreamLine("elapsed_time: %d", elapsed_time);
			//writeDebugStreamLine("current_read_time: %d", current_read_time);
			//writeDebugStreamLine("shooter_target_speed: %d", shooter_target_speed);
			// writeDebugStreamLine("right shooter power: %d", motor[rightTopShooter]);

			print_value = 0;
		}
		delay(500);

	}
}



task main()
{

startTask(shooter_power_control);
}
