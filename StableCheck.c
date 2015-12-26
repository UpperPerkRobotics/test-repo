int rightStableList[20];
int leftStableList[20];


void purgeLeftValues(){
  for(int i=0; i < 20; i++){
 		leftStableList[i] = 0;
 }
}

void purgeRightValues(){
 for(int i=0; i < 20; i++){
 		rightStableList[i] = 0;
 }
}

bool stableCheck( int * list){

	int total = 0;
	int average = 0;
	int maxrange;
	int minrange;
	for(int i=0; i < 20; i++){
		total = total +	list[i];
	}
		average = total / 20;
		maxrange = average * 1.04;
		minrange = average * 0.96;

		bool stable = true;
	for(int i=0; i < 20; i++){
		if ((list[i] > maxrange) || (list[i] < minrange)){
		stable = false;
		}
	}
	return stable;
}

bool isLeftStable (int currentSpeed){
	// maintain left list
	for(int i=19; i > 0; --i){
			leftStableList[i] = leftStableList[i-1];
	}

	leftStableList[0] = currentSpeed;
	//get total
	return stableCheck(leftStableList);
}
bool isRightStable (int currentSpeed){
	// maintain list
	for(int i = 19; i > 0; --i){
			rightStableList[i] = rightStableList[i-1];
	}


	rightStableList[0] = currentSpeed;
	// get total
	return stableCheck(rightStableList);
}