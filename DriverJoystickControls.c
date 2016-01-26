// Read Buttons to see if any are pushed

bool driveTrainReversed = false;
bool manualIntake = false;

task controllerPolling(){
	while(true){
		// Check each button and do actions
		if((vexRT[Btn8U] == 1) || (vexRT[Btn8UXmtr2] == 1)){
			// Set motor target speed (Far), Channel 8, Button U
			set_shooter_targets(890);
			delay(500);
		}
		else if((vexRT[Btn8R] == 1) || (vexRT[Btn8RXmtr2] == 1)){
			// Set motor target speed (Medium), Channel 8, Button R
			set_shooter_targets(780);
			delay(500);
		}
		else if((vexRT[Btn8D] == 1) || (vexRT[Btn8DXmtr2] == 1)){
			// Set motor target speed (Short), Channel 8, Button D
			set_shooter_targets(620);
			delay(500);
		}
		else if((vexRT[Btn6U] == 1) || (vexRT[Btn6UXmtr2] == 1)){
			// Adjust motor target speed (5 up), Channel 6, Button U
			adjust_shooter_targets(10);
			delay(250);
		}
		else if((vexRT[Btn6D] == 1) || (vexRT[Btn6DXmtr2] == 1)){
			// Adjust motor target speed (5 down), Channel 6, Button D
			adjust_shooter_targets(-10);
			delay(500);
		}
		else if((vexRT[Btn8L] == 1) || (vexRT[Btn8LXmtr2] == 1)){
			// Stop all motor speed (0), Channel 8, Button L
			if (shooter_target_speed == 0){
				if (backOut == false)
					toggleShooterWheels = true;
				backOut = true;
			}
			set_shooter_targets(0);
			delay(500);
		}
		else if (backOut){
			toggleShooterWheels = true;
			backOut = false;
		}


		else if((vexRT[Btn7U] == 1) || (vexRT[Btn7UXmtr2] == 1)){
			// Forward Intake, Channel 7, Button U
			manualIntake = false;
			setIntakeSpeed(100);
			delay(250);
		}
		else if((vexRT[Btn7D] == 1) || (vexRT[Btn7DXmtr2] == 1)){
			manualIntake = false;
			// Backward Intake, Channel 7, Button D
			setIntakeSpeed(-100);
			delay(250);
		}
		else if((vexRT[Btn7L] == 1) || (vexRT[Btn7LXmtr2] == 1)){
			manualIntake = false;
			// Stop Intake, Channel 7, Button L
			setIntakeSpeed(0);
			delay(250);
		}
		else if(vexRT[Btn7R] == 1){
			// Reverse drive train to enable easier intake control
			driveTrainReversed = !driveTrainReversed;
			setHeadLights(driveTrainReversed);
			delay(500);
		}
		delay(10);
	}
}

// Add driver joystick Controls here
task driving(){

	while(true)
	{
		if(driveTrainReversed == false){

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
		}

		else {
			//writeDebugStreamLine("***** Drive Loop ******");
			if((vexRT[Ch2] > 20) || (vexRT[Ch2] < -20))
			{
				//writeDebugStreamLine("***** Right Side Go ******");
				motor[leftDrive] = (vexRT[Ch2] * -1);
			}
			else {
				motor[leftDrive] = 0;
			}

			if((vexRT[Ch3] > 20) || (vexRT[Ch3] < -20))
			{
				motor[rightDrive] = (vexRT[Ch3] * -1);
			}
			else {
				motor[rightDrive] = 0;
			}

		}
		//Intake Joystick Control
		//writeDebugStreamLine("***** Drive Loop ******");
		if((vexRT[Ch2Xmtr2] > 20) || (vexRT[Ch2Xmtr2] < -20))
		{
			//writeDebugStreamLine("***** Right Side Go ******");
			manualIntake = true;
			motor[rightIntake] = vexRT[Ch2Xmtr2];
			motor[leftIntake] = vexRT[Ch2Xmtr2];
		}
		else {
			if(manualIntake){
				motor[rightIntake] = 0;
				motor[leftIntake] = 0;
			}
		}

		// Lifter controls

		if((vexRT[Btn5U] == 1) || (vexRT[Btn5UXmtr2] == 1)){
			motor[rightLifter] = 80;
			motor[leftLifter] = 80;
		}
		else if((vexRT[Btn5D] == 1) || (vexRT[Btn5UXmtr2] == 1)){
			motor[rightLifter] = -80;
			motor[leftLifter] = -80;
		}
		else {
			motor[rightLifter] = 0;
			motor[leftLifter] = 0;
		}
		delay(50);
	}
}
// End Driver joystick Controls
