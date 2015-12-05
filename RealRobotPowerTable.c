int getRightShooterPower(int speed){
	int power = 0;
	if (speed > 1300){
		power = 82;
	}
	else if (speed > 1266){
		power = 80;
	}
	else if (speed > 1233){
		power = 78;
	}
	else if (speed > 1200){
		power = 76;
	}
	else if (speed > 1166){
		power = 74;
	}
	else if (speed > 1133){
		power = 72;
	}
	else if (speed > 1100){
		power = 70;
	}
	else if (speed > 1050){
		power = 68;
	}
	else if (speed > 1030){
		power = 66;
	}
	else if (speed > 1000){
		power = 64;
	}
	else if (speed > 966){
		power = 62;
	}
	else if (speed > 933){
		power = 60;
	}
	else if (speed > 900){
		power = 56;
	}
	else if (speed > 866){
		power = 56;
	}
	else if (speed > 833){
		power = 52;
	}
	else if (speed > 800){
		power = 50;
	}
	else if (speed > 766){
		power = 48;
	}
	else if (speed > 733){
		power = 46;
	}
	else if (speed > 700){
		power = 44;
	}
	else if (speed > 666){
		power = 42;
	}
	else if (speed > 633){
		power = 40;
	}
	else if (speed > 600){
		power = 38;
	}
	else if (speed > 100){
		power = 20;
	}
	else {
		power = 0;
	}
	return power;

}

int getLeftShooterPower(int speed){
	int power = 0;
	if (speed > 1300){
		power = 88;
	}
	else if (speed > 1266){
		power = 86;
	}
	else if (speed > 1233){
		power = 84;
	}
	else if (speed > 1200){
		power = 82;
	}
	else if (speed > 1166){
		power = 80;
	}
	else if (speed > 1133){
		power = 78;
	}
	else if (speed > 1100){
		power = 76;
	}
	else if (speed > 1050){
		power = 74;
	}
	else if (speed > 1030){
		power = 70;
	}
	else if (speed > 1000){
		power = 68;
	}
	else if (speed > 966){
		power = 66;
	}
	else if (speed > 933){
		power = 64;
	}
	else if (speed > 900){
		power = 60;
	}
	else if (speed > 866){
		power = 58;
	}
	else if (speed > 833){
		power = 56;
	}
	else if (speed > 800){
		power = 54;
	}
	else if (speed > 766){
		power = 52;
	}
	else if (speed > 733){
		power = 50;
	}
	else if (speed > 700){
		power = 48;
	}
	else if (speed > 666){
		power = 46;
	}
	else if (speed > 633){
		power = 44;
	}
	else if (speed > 600){
		power = 42;
	}
	else if (speed > 100){
		power = 20;
	}
	else {
		power = 0;
	}
	return power;
}
