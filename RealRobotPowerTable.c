int getRightShooterPower(int speed){
	int power = 0;
	if (speed > 940){
		power = 110;
	}
	else if (speed > 880){
		power = 80;
	}
	else if (speed > 870){
		power = 79;
	}
	else if (speed > 865){
		power = 78;
	}
	else if (speed > 860){
		power = 77;
	}
	else if (speed > 855){
		power = 76;
	}
	else if (speed > 850){
		power = 75;
	}
	else if (speed > 848){
		power = 74;
	}
	else if (speed > 846){
		power = 73;
	}
	else if (speed > 844){
		power = 72;
	}
	else if (speed > 842){
		power = 71;
	}
	else if (speed > 840){
		power = 70;
	}
	else if (speed > 835){
		power = 69;
	}
	else if (speed > 830){
		power = 68;
	}
	else if (speed > 820){
		power = 66;
	}
	else if (speed > 810){
		power = 65;
	}
	else if (speed > 805){
		power = 64;
	}
	else if (speed > 800){
		power = 63;
	}
	else if (speed > 790){
		power = 62;
	}
	else if (speed > 780){
		power = 61;
	}
	else if (speed > 770){
		power = 60;
	}
	else if (speed > 760){
		power = 58;
	}
		else if (speed > 750){
		power = 57;
	}
	else if (speed > 747){
		power = 56;
	}
	else if (speed > 745){
		power = 55;
	}
		else if (speed > 730){
		power = 54;
	}
	else if (speed > 710){
		power = 52;
	}
		else if (speed > 690){
		power = 51;
	}
	else if (speed > 670){
		power = 50;
	}
		else if (speed > 665){
		power = 49;
	}
	else if (speed > 660){
		power = 48;
	}
		else if (speed > 650){
		power = 47;
	}
	else if (speed > 640){
		power = 46;
	}
		else if (speed > 630){
		power = 45;
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
  if (speed > 860){
		power = 80;
	}
		else if (speed > 854){
		power = 79;
	}
	else if (speed > 848){
		power = 78;
	}
		else if (speed > 842){
		power = 77;
	}
	else if (speed > 836){
		power = 76;
	}
		else if (speed > 830){
		power = 75;
	}
	else if (speed > 820){
		power = 74;
	}
		else if (speed > 810){
		power = 72;
	}
	else if (speed > 800){
		power = 70;
	}
		else if (speed > 794){
		power = 69;
	}
	else if (speed > 788){
		power = 68;
	}
		else if (speed > 782){
		power = 67;
	}
	else if (speed > 776){
		power = 66;
	}
		else if (speed > 770){
		power = 65;
	}
	else if (speed > 755){
		power = 64;
	}
		else if (speed > 745){
		power = 62;
	}
	else if (speed > 730){
		power = 60;
	}
		else if (speed > 722){
		power = 59;
	}
	else if (speed > 714){
		power = 58;
	}
		else if (speed > 706){
		power = 57;
	}
	else if (speed > 698){
		power = 56;
	}
		else if (speed > 690){
		power = 55;
	}
	else if (speed > 680){
		power = 54;
	}
		else if (speed > 655){
		power = 53;
	}
	else if (speed > 640){
		power = 52;
	}
		else if (speed > 625){
		power = 51;
	}
	else if (speed > 620){
		power = 50;
	}
		else if (speed > 610){
		power = 49;
	}
	else if (speed > 600){
		power = 48;
	}
		else if (speed > 590){
		power = 47;
	}
	else if (speed > 580){
		power = 46;
	}
		else if (speed > 570){
		power = 45;
	}
	else if (speed > 100){
		power = 20;
	}
	else {
		power = 0;
	}
	return power;
}
