#define BUFFER_SIZE 18

int rightStableList[BUFFER_SIZE];
int leftStableList[BUFFER_SIZE];


void purgeLeftValues(){
  for(int i=0; i < BUFFER_SIZE; i++){
 		leftStableList[i] = 0;
 }
}

void purgeRightValues(){
 for(int i=0; i < BUFFER_SIZE; i++){
 		rightStableList[i] = 0;
 }
}

int stableCheck( int * list){

	int total = 0;
	int average = 0;
	int maxrange;
	int minrange;
	int forecast = 0;
	int firstHalfTotal = 0;
	int firstHalfAve = 0;
	int secondHalfTotal = 0;
	int secondHalfAve = 0;

	for(int i=0; i < BUFFER_SIZE; i++){
		total = total +	list[i];
		if (i < (BUFFER_SIZE / 2)){
			firstHalfTotal = firstHalfTotal + list[i];
		}
		else{
			secondHalfTotal = secondHalfTotal + list[i];
		}
	}
	average = total / BUFFER_SIZE;
	firstHalfAve = (firstHalfTotal / (BUFFER_SIZE / 2));
	secondHalfAve = (secondHalfTotal / (BUFFER_SIZE / 2));
	maxrange = average * 1.04;
	minrange = average * 0.96;

	bool stable = true;
	for(int i=0; i < BUFFER_SIZE; i++){
		if ((list[i] > maxrange) || (list[i] < minrange)){
			stable = false;
		}
	}
	if (stable)
		// Weighted average change forecast
		// return the second half average with 1/2 the difference between first and second halfs
		return secondHalfAve + ((secondHalfAve - firstHalfAve) / 2);
	else
		return 0;
}

int isLeftStable (int currentSpeed){
	// maintain left list
	for(int i=(BUFFER_SIZE - 1); i > 0; --i){
			leftStableList[i] = leftStableList[i-1];
	}
	leftStableList[0] = currentSpeed;
	//get total
	return stableCheck(leftStableList);
}
int isRightStable (int currentSpeed){
	// maintain list
	for(int i = (BUFFER_SIZE - 1); i > 0; --i){
			rightStableList[i] = rightStableList[i-1];
	}
	rightStableList[0] = currentSpeed;
	// get total
	return stableCheck(rightStableList);
}
