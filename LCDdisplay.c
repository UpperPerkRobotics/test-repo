char *options[3];
const int optionCount = 3;

const int leftButton = 1;
const int centerButton = 2;
const int rightButton = 4;


void setOptions(){
		options[0] = "Do stuff";
		options[1] = "Other";
		options[2] = "Meh";
}

task main()
{
	setOptions();
	int option = 0;
	int selection = -1;
	while(nLCDButtons != centerButton){
 		displayLCDCenteredString(0, options[option]);
 		delay(500);
 		if(nLCDButtons ==	leftButton){
 			if (option == 0)
 				option = optionCount - 1;
 			else
 				option = option - 1;
 		}
 		if(nLCDButtons ==	rightButton){
 			if (option == (optionCount - 1))
 				option = 0;
 			else
 				option = option + 1;
 		}
	}
	 selection = option;
	 displayLCDCenteredString(0, "You selected");
	 displayLCDCenteredString(1, options[selection]);
	 delay(10000);

}
