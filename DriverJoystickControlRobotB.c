// Read Buttons to see if any are pushed

bool strafeMode = false;
bool manualIntake = false;
bool turning = false;
bool turnBreaking = false;
int lastTurnError = 0;

task controllerPolling(){

	while(true){
		// Check each button and do actions
		if((vexRT[Btn8U] == 1) || (vexRT[Btn8UXmtr2] == 1)){
			// Set motor target speed (Far), Channel 8, Button U
			// set_shooter_targets(850);
			delay(500);
		}
		else if((vexRT[Btn8R] == 1) || (vexRT[Btn8RXmtr2] == 1)){
			// Set motor target speed (Medium), Channel 8, Button R
			//set_shooter_targets(700);
			delay(500);
		}
		else if((vexRT[Btn8D] == 1) || (vexRT[Btn8DXmtr2] == 1)){
			// Set motor target speed (Short), Channel 8, Button D
			//set_shooter_targets(590);
			delay(500);
		}
		else if((vexRT[Btn6U] == 1) || (vexRT[Btn6UXmtr2] == 1)){
			// Adjust motor target speed (5 up), Channel 6, Button U
		//	adjust_shooter_targets(10);
			delay(250);
		}
		else if((vexRT[Btn6D] == 1) || (vexRT[Btn6DXmtr2] == 1)){
			// Adjust motor target speed (5 down), Channel 6, Button D
			//adjust_shooter_targets(-10);
			delay(500);
		}
		else if((vexRT[Btn8L] == 1) || (vexRT[Btn8LXmtr2] == 1)){
			// Stop all motor speed (0), Channel 8, Button L

		}


		else if((vexRT[Btn7U] == 1) || (vexRT[Btn7UXmtr2] == 1)){
			// Forward Intake, Channel 7, Button U
			motor[intake] = 100;
			delay(250);
		}
		else if((vexRT[Btn7D] == 1) || (vexRT[Btn7DXmtr2] == 1)){
			// Backward Intake, Channel 7, Button D
			motor[intake] = -100;
			delay(250);
		}
		else if((vexRT[Btn7L] == 1) || (vexRT[Btn7LXmtr2] == 1)){
			// Stop Intake, Channel 7, Button L
			motor[intake] = 0;
			delay(250);
		}
		else if(vexRT[Btn5U] == 1){
			// Turn drive train into strafe mode to enable easier access around the field
			strafeMode = !strafeMode;
			if(strafeMode){
				SensorValue[in1] = 0;
			}

			delay(250);
		}
		delay(10);
	}
}

// Add driver joystick Controls here
task driving(){

	while(true)
	{
		// Tank Drive Mode
		if(strafeMode == false){

			//Right Drive;
			if((vexRT[Ch2] > 20) || (vexRT[Ch2] < -20))
			{
				turning = true;
				turnBreaking = false;
				motor[rightDrive] = vexRT[Ch2];
			}
			else {
				if (turnBreaking){
					motor[rightDrive] = -1 * (SensorValue[in1] / 2);
				}
				else{
					motor[rightDrive] = 0;
				}
			}

			// Left Drive
			if((vexRT[Ch3] > 20) || (vexRT[Ch3] < - 20))
			{
				turning = true;
				turnBreaking = false;
				motor[leftDrive] = vexRT[Ch3];
			}
			else {
				if (turning){
					motor[leftDrive] = 0;
				}
				else{
					motor[leftDrive] = (SensorValue[in1] / 2);
				}
			}

			// Should be stopped
			if(((vexRT[Ch3] < 20) && (vexRT[Ch3] > - 20)) &&
				((vexRT[Ch2] < 20) && (vexRT[Ch2] > - 20))){
					if(turning){
						turning = false;
						lastTurnError = 0;
						SensorValue[in1] = 0;
						turnBreaking = true;
					}
					if (turnBreaking){
						if (abs(SensorValue[in1]) >= abs(lastTurnError)) // errors getting worse
							lastTurnError = SensorValue[in1];
						else
							turnBreaking = false;
					}
				}
		}
//In strafeMode
		else {
			//writeDebugStreamLine("***** Drive Loop ******");
			if ((vexRT[Ch3] > 20) || (vexRT[Ch3] < -20) ||
				  (vexRT[Ch4] > 20) || (vexRT[Ch4] < -20))
			{
				motor[rightDrive] 	= vexRT[Ch3] - (SensorValue[in1] / 10);
				motor[leftDrive] 		= vexRT[Ch3] + (SensorValue[in1] / 10);
				motor[strafeDrive] 	= (vexRT[Ch4] );
			}
			else {
				motor[strafeDrive] = 0;
				motor[rightDrive] = 0;
				motor[leftDrive] = 0;
			}
		}
		//Intake Joystick Control
		//writeDebugStreamLine("***** Drive Loop ******");
		if((vexRT[Ch2Xmtr2] > 20) || (vexRT[Ch2Xmtr2] < -20))
		{
			motor[intake] = vexRT[Ch2Xmtr2];
		}

		// Shooter controls

		if((vexRT[Btn5U] == 1) || (vexRT[Btn5UXmtr2] == 1)){
			motor[shooterLeft] = 127;
			motor[shooterRight] = -127;
		}
		else {
			motor[shooterLeft] = 0;
			motor[shooterRight] = 0;
		}
		delay(50);
	}
}
// End Driver joystick Controls
