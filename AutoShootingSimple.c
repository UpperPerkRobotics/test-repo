void simpleAutoIntake(int cycles){
	for (int i =0; i< cycles; i++){
		delay(1000);
		setIntakeSpeed(100);
		delay(1000);
		setIntakeSpeed(0);
	}
}
