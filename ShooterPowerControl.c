#pragma config(Sensor, dgtl1,	 rightShooter,	 sensorQuadEncoder)
#pragma config(Sensor, dgtl3,	 leftShooter,		 sensorQuadEncoder)
#pragma config(Motor,	 port4,						topRight,			 tmotorVex393_MC29, openLoop)
#pragma config(Motor,	 port5,						bottomRight,	 tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,	 port6,						topLeft,			 tmotorVex393_MC29, openLoop)
#pragma config(Motor,	 port7,						bottomLeft,		 tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard							 !!*//

int shooter_target_speed = 0;

task shooter_power_control()
{
	int last_encoder_clicks = 0;
	int last_read_time = 0;

	while(true)
	{
		int current_click = SensorValue[rightShooter];
		int current_read_time = nPgmTime;

		int elapsed_clicks = current_click - last_encoder_clicks;
		int elapsed_time = current_read_time - last_read_time;

		int current_speed = elapsed_clicks/elapsed_time;

			if (current_speed < shooter_target_speed)
			{
				motor[topRight] =  127;
				motor[bottomRight] = 127;
			}
			else if (current_speed >= shooter_target_speed)
			{
				motor[topRight] = 0;
				motor[bottomRight] = 0;
			}
			last_encoder_clicks = current_click;
			last_read_time = current_read_time;
	}
}


task main()
{
startTask (shooter_power_control);


}
