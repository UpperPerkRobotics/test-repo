#define GREEN 0
#define YELLOW 1
#define RED 2
#define ALL 3
#define NONE 4

void setRedLight (bool on)
{
	if (on){
		SensorValue[RedLight] = 1;
	}
	else {
		SensorValue[RedLight] = 0;
	}
}

void setYellowLight (bool on)
{
	if (on){
		SensorValue[YellowLight] = 1;
	}
	else {
		SensorValue[YellowLight] = 0;
	}
}
void setGreenLight (bool on)
{
	if (on){
		SensorValue[GreenLight] = 1;
	}
	else {
		SensorValue[GreenLight] = 0;
	}
}

void setStopLight(int color)
{
	if (color==GREEN){
		setRedLight(false);
		setYellowLight(false);
		setGreenLight(true);
	}
	else if (color==YELLOW){
		setRedLight(false);
		setYellowLight(true);
		setGreenLight(false);
	}
	else if (color==RED){
		setRedLight(true);
		setYellowLight(false);
		setGreenLight(false);
	}
	else if (color==ALL){
		setRedLight(true);
		setYellowLight(true);
		setGreenLight(true);
	}
	else if (color==NONE){
		setRedLight(false);
		setYellowLight(false);
		setGreenLight(false);
	}
}
