
#include "RealRobotPowerTable.c"

task main()
{
	writeDebugStreamLine("Left Power for 1000: %d", getLeftShooterPower(1000));
	writeDebugStreamLine("Right Power for 1000: %d", getRightShooterPower(1000));

		writeDebugStreamLine("Left Power for 900: %d", getLeftShooterPower(900));
	writeDebugStreamLine("Right Power for 900: %d", getRightShooterPower(900));
		writeDebugStreamLine("Left Power for 600: %d", getLeftShooterPower(600));
	writeDebugStreamLine("Right Power for 600: %d", getRightShooterPower(600));
		writeDebugStreamLine("Left Power for 800: %d", getLeftShooterPower(800));
	writeDebugStreamLine("Right Power for 800: %d", getRightShooterPower(800));
		writeDebugStreamLine("Left Power for 750: %d", getLeftShooterPower(750));
	writeDebugStreamLine("Right Power for 750: %d", getRightShooterPower(750));


}
