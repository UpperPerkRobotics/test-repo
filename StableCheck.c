int rightStableList[5];
int leftStableList[5];



bool stableCheck( int * list){

	int total = 0;
	int average = 0;
	int maxrange;
	int minrange;
	for(int i=0; i < 5; i++){
		total = total +	list[i];
	}
		average = total / 5;
		maxrange = average * 1.03;
		minrange = average * 0.97;

		bool stable = true;
	for(int i=0; i < 5; i++){
		if ((list[i] > maxrange) || (list[i] < minrange)){
		stable = false;
		}
	}
	return stable;
}

bool isLeftStable (int currentSpeed){
	// maintain left list
	for(int i=4; i > 0; --i){
			leftStableList[i] = leftStableList[i-1];
	}

	leftStableList[0] = currentSpeed;
	//get total
	return stableCheck(leftStableList);
}
bool isRightStable (int currentSpeed){
	// maintain list
	for(int i = 4; i > 0; --i){
			rightStableList[i] = rightStableList[i-1];
	}


	rightStableList[0] = currentSpeed;
	// get total
	return stableCheck(rightStableList);
}
