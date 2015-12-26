#include "AutoShooting.c"
task main()
{
	writeDebugStreamLine("isShooterReady with 0 green out of 10 counts %s", isShooterReady(0,10)? "true":"false");
	writeDebugStreamLine("isShooterReady with 10 green out of 10 counts %s", isShooterReady(10,10)? "true":"false");
	writeDebugStreamLine("isShooterReady with 8 green out of 10 counts %s", isShooterReady(8,10)? "true":"false");
	writeDebugStreamLine("isShooterReady with 10 green out of 10 counts %s", isShooterReady(10,10)? "true":"false");
	writeDebugStreamLine("isShooterReady with 13 green out of 20 counts %s", isShooterReady(13,20)? "true":"false");
	writeDebugStreamLine("isShooterReady with 10 green out of 20 counts %s", isShooterReady(10,20)? "true":"false");
	writeDebugStreamLine("isShooterReady with 15 green out of 20 counts %s", isShooterReady(15,20)? "true":"false");
	writeDebugStreamLine("isShooterReady with 19 green out of 20 counts %s", isShooterReady(19,20)? "true":"false");


}
