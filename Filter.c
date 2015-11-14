int rightValues[5];
int leftValues[5];

int doFilter(int * valueList) {
	// get total
	int total = 0;


	int biggest = valueList[0];
	int lowest = valueList[0];


	for(int i = 0; i < 5; i++){
			total += valueList[i];

			if(valueList[i] > biggest){
				biggest = valueList[i];
			}

			if(valueList[i] < lowest){
				lowest = valueList[i];
			}

	}
int filteredTotal = total - (biggest + lowest);
int filterAverage = (filteredTotal/3);

return filterAverage;

}

int filterLeft(int value){
	// maintain left list
	for(int i=4; i > 0; --i){
			leftValues[i] = leftValues[i-1];
	}

	leftValues[0] = value;
	//get total
	return doFilter(leftValues);
}

int filterRight(int value){
	// maintain list
	for(int i = 4; i > 0; --i){
			rightValues[i] = rightValues[i-1];
	}

	rightValues[0] = value;
	// get total
	return doFilter(rightValues);
}
