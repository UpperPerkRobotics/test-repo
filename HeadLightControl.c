void setFrontLED (bool on)
{
	if (on){
		SensorValue[FrontLED] = 1;
	}
	else {
		SensorValue[FrontLED] = 0;
	}
}


void setBackLED (bool on)
{
	if (on){
		SensorValue[BackLED] = 1;
	}
	else {
		SensorValue[BackLED] = 0;
	}
}


void setHeadLights (bool reverse){
 if (reverse)
 {
   setBackLED(true);
   setFrontLED(false);
 }
 else
 {
   setFrontLED(true);
   setBackLED(false);
 }
}
