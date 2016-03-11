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
			// Intake Forward only, apply breaking power to expeller
			motor[intake] = 127;
		}
		else if((vexRT[Btn6D] == 1) || (vexRT[Btn6DXmtr2] == 1)){
			// Intake Reverse
			motor[intake] = -100;
		}
		else if((vexRT[Btn8L] == 1) || (vexRT[Btn8LXmtr2] == 1)){
			// Stop all motor speed (0), Channel 8, Button L

		}
		else if((vexRT[Btn7U] == 1) || (vexRT[Btn7UXmtr2] == 1)){
			// Forward Intake, Channel 7, Button U
			delay(250);
		}
		else if((vexRT[Btn7D] == 1) || (vexRT[Btn7DXmtr2] == 1)){
			// Backward Intake, Channel 7, Button D
			delay(250);
		}
		else if((vexRT[Btn7L] == 1) || (vexRT[Btn7LXmtr2] == 1)){
			// Stop Intake, Channel 7, Button L
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
		else{
			motor[intake] = 0;
			motor[expeller] = 0;
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
					motor[rightDrive] = -1 * sgn(SensorValue[in1]) * 15;
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
				if (turnBreaking){
					motor[leftDrive] = sgn(SensorValue[in1]) * 15;
				}
				else{
					motor[leftDrive] = 0;
				}
			}

			// Should be stopped
			if(((vexRT[Ch3] < 20) && (vexRT[Ch3] > - 20)) &&
				((vexRT[Ch2] < 20) && (vexRT[Ch2] > - 20))){
					if (turnBreaking){
						if (abs(SensorValue[in1]) > (abs(lastTurnError) + 3)) // errors getting worse (surpress noise with 3)
							lastTurnError = SensorValue[in1];
						else
							turnBreaking = false;
					}
					if(turning){
						turning = false;
						lastTurnError = 0;
						SensorValue[in1] = 0;
						turnBreaking = true;
					}
				}
		}
//In strafeMode
		else {
			//writeDebugStreamLine("***** Drive Loop ******");
			if ((vexRT[Ch3] > 20) || (vexRT[Ch3] < -20) ||
				  (vexRT[Ch1] > 20) || (vexRT[Ch1] < -20))
			{
				motor[rightDrive] 	= vexRT[Ch3] - (SensorValue[in1] / 4);
				motor[leftDrive] 		= vexRT[Ch3] + (SensorValue[in1] / 4);
				motor[strafeDrive] 	= vexRT[Ch1];
				motor[strafeFront]  = vexRT[Ch1];
			}
			else {
				motor[strafeDrive] = 0;
				motor[strafeFront] = 0;
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

		if((vexRT[Btn5D] == 1) || (vexRT[Btn5DXmtr2] == 1)){
			motor[shooterLeft] = 127;
			motor[shooterRight] = -127;
		}
		else {
			motor[shooterLeft] = 0;
			motor[shooterRight] = 0;
		}
		delay(5);
	}
}
// End Driver joystick Controls
