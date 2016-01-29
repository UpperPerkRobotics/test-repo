#define STOPPED 0
#define READY_TO_SHOOT 1
#define RECOVERY 2
#define NORMAL 3

int ShooterMode = STOPPED;
bool leftHitStable = false;
bool rightHitStable = false;
bool hipshot = false;
int ballsFiredCount = 0;


bool isShooterReady (int greencounts,int loopcounts){
	if (ShooterMode == READY_TO_SHOOT)
		return true;
  else if (leftHitStable && rightHitStable)
  	return true;
	else if ((greencounts >= (.75 * loopcounts)) && (loopcounts > 8))
		return true;
	else
		return false;
}

void ballFireDetected(){
	ballsFiredCount = ballsFiredCount + 1;
	ShooterMode = RECOVERY;
	writeDebugStreamLine("Ball Fired Detected: Ball #%d", ballsFiredCount);
}


void setIntakeSpeed(int speed){
	motor[leftIntake] = speed;
	motor[rightIntake] = speed;
}

task AutoIntake(){
	while (true){
		if ((ShooterMode == READY_TO_SHOOT) || (hipshot == true)){
				setIntakeSpeed(100);
		}
		else{
				setIntakeSpeed(0);
		}
	delay (50);
	}
}
