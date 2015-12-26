#define BUFFER_SIZE 15

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

bool stableCheck( int * list){

	int total = 0;
	int average = 0;
	int maxrange;
	int minrange;
	for(int i=0; i < BUFFER_SIZE; i++){
		total = total +	list[i];
	}
		average = total / BUFFER_SIZE;
		maxrange = average * 1.05;
		minrange = average * 0.95;

		bool stable = true;
	for(int i=0; i < BUFFER_SIZE; i++){
		if ((list[i] > maxrange) || (list[i] < minrange)){
		stable = false;
		}
	}
	return stable;
}

bool isLeftStable (int currentSpeed){
	// maintain left list
	for(int i=(BUFFER_SIZE - 1); i > 0; --i){
			leftStableList[i] = leftStableList[i-1];
	}
	leftStableList[0] = currentSpeed;
	//get total
	return stableCheck(leftStableList);
}
bool isRightStable (int currentSpeed){
	// maintain list
	for(int i = (BUFFER_SIZE - 1); i > 0; --i){
			rightStableList[i] = rightStableList[i-1];
	}
	rightStableList[0] = currentSpeed;
	// get total
	return stableCheck(rightStableList);
}
