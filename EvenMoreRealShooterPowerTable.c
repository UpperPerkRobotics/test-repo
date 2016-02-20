int getShooterPower(int speed){
	int power = 0;
  if (speed > 975){
		power = 70;
	}
	else if (speed > 96){
		power = 69;
	}
	else if (speed > 94){
		power = 68;
	}
	else if (speed > 92){
		power = 67;
	}
	else if (speed > 90){
		power = 66;
	}

	else if (speed > 88){
		power = 65;
	}
	else if (speed > 86){
		power = 64;
	}
	else if (speed > 84){
		power = 63;
	}
	else if (speed > 82){
		power = 62;
	}

	else if (speed > 80){
		power = 61;
	}
	else if (speed > 78){
		power = 60;
	}
		else if (speed > 76){
		power = 59;
	}
	else if (speed > 74){
		power = 58;
	}
		else if (speed > 72){
		power = 57;
	}
	else if (speed > 70){
		power = 56;
	}
		else if (speed > 68){
		power = 55;
	}
	else if (speed > 66){
		power = 54;
	}
		else if (speed > 64){
		power = 53;
	}
	else if (speed > 62){
		power = 52;
	}
		else if (speed > 60){
		power = 51;
	}
	else if (speed > 58){
		power = 50;
	}
		else if (speed > 56){
		power = 49;
	}
	else if (speed > 54){
		power = 48;
	}
		else if (speed > 52){
		power = 47;
	}
	else if (speed > 50){
		power = 46;
	}
		else if (speed > 48){
		power = 45;
	}
	else if (speed > 46){
		power = 44;
	}
		else if (speed > 44){
		power = 43;
	}
	else if (speed > 698){
		power = 42;
	}
		else if (speed > 690){
		power = 41;
	}
	else if (speed > 680){
		power = 40;
	}
		else if (speed > 655){
		power = 39;
	}
	else if (speed > 640){
		power = 38;
	}
		else if (speed > 625){
		power = 37;
	}
	else if (speed > 620){
		power = 36;
	}
		else if (speed > 610){
		power = 35;
	}
	else if (speed > 600){
		power = 34;
	}
		else if (speed > 590){
		power = 33;
	}
	else if (speed > 580){
		power = 32;
	}
		else if (speed > 570){
		power = 31;
	}
	else if (speed > 560){
		power = 30;
	}
	else if (speed > 550){
		power = 29;
	}
	else if (speed > 540){
		power = 28;
	}
	else if (speed > 530){
		power = 27;
	}
	else if (speed > 520){
		power = 26;
	}
	else if (speed > 510){
		power = 25;
	}
	else if (speed > 500){
		power = 24;
	}
	else if (speed > 490){
		power = 23;
	}
	else if (speed > 480){
		power = 22;
	}
	else if (speed > 470){
		power = 21;
	}
	else if (speed > 460){
		power = 20;
	}
	else if (speed > 450){
		power = 19;
	}
	else if (speed > 440){
		power = 18;
	}
	else if (speed > 430){
		power = 17;
	}
	else if (speed > 420){
		power = 16;
	}
	else if (speed > 410){
		power = 15;
	}
	else if (speed > 400){
		power = 14;
	}
	else if (speed > 100){
		power = 5;
	}
	else {
		power = 0;
	}
	return power;
}
