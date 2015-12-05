// Read Buttons to see if any are pushed
int shooter_target_speed = 0;

void set_shooter_targets(int speed){
	// For now, set value and print a debug statement
	shooter_target_speed = speed;
	// shooter_target_power = power;
	writeDebugStreamLine("Shooter Target Speed: %d", shooter_target_speed);
}

void adjust_shooter_targets(int adjust_speed){
	// For now, adjust value a bit, and print a debug statement
	shooter_target_speed = shooter_target_speed + adjust_speed;
	// shooter_target_power = shooter_target_power + adjust_power;
	writeDebugStreamLine("Shooter Target Speed: %d", shooter_target_speed);
}

void setIntakeSpeed(int speed){
	motor[leftIntake] = speed;
	motor[rightIntake] = speed;
}

task controllerPolling(){
	while(true){
		// Check each button and do actions
		if(vexRT[Btn8U] == 1){
			// Set motor target speed (Far), Channel 8, Button U
			set_shooter_targets(1000);
			delay(500);
		}
		else if(vexRT[Btn8R] == 1){
			// Set motor target speed (Medium), Channel 8, Button R
			set_shooter_targets(900);
			delay(500);
		}
		else if(vexRT[Btn8D] == 1){
			// Set motor target speed (Short), Channel 8, Button D
			set_shooter_targets(800);
			delay(500);
		}
		else if(vexRT[Btn6U] == 1){
			// Adjust motor target speed (5 up), Channel 6, Button U
			adjust_shooter_targets(4);
			delay(250);
		}
		else if(vexRT[Btn6D] == 1){
			// Adjust motor target speed (5 down), Channel 6, Button D
			adjust_shooter_targets(-4);
			delay(250);
		}
		else if(vexRT[Btn8L] == 1){
			// Stop all motor speed (0), Channel 8, Button L
			set_shooter_targets(0);
			delay(250);
		}
		else if(vexRT[Btn7U] == 1){
			// Forward Intake, Channel 7, Button U
			setIntakeSpeed(100);
			delay(250);
		}
		else if(vexRT[Btn7D] == 1){
			// Backward Intake, Channel 7, Button D
			setIntakeSpeed(-100);
			delay(250);
		}
		else if(vexRT[Btn7L] == 1){
			// Stop Intake, Channel 7, Button L
			setIntakeSpeed(0);
			delay(250);
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
