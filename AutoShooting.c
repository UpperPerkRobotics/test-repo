#define STOPPED 0
#define READY_TO_SHOOT 1
#define RECOVERY 2
#define NORMAL 3

int ShooterMode = STOPPED;

bool isShooterReady (int greencounts,int loopcounts){
if (ShooterMode == READY_TO_SHOOT)
	return true;
else if ((greencounts >= (.75 * loopcounts)) &&(loopcounts > 10))
	return true;
else
	return false;
}

void setIntakeSpeed(int speed){
	motor[leftIntake] = speed;
	motor[rightIntake] = speed;
}

task AutoIntake(){
	while (true){
		if (ShooterMode == READY_TO_SHOOT){
				setIntakeSpeed(100);
		}
		else{
				setIntakeSpeed(0);
		}
	delay (50);
	}
}
