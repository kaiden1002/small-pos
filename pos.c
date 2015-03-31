#include "pos.h"

int main() {
	
	//variables
	char input[50];
	int centsOwed;
	int centsPaid;
	int running = RUN;
	int action = MAIN;
	int sellAction = START;
	
	//main program loop
	while(running) {
		//switch statement controls what part of the program to run based on the action variable
		switch(action){
		//main case or main menu of the program
		case MAIN:
			printPrompt(MAIN);
			scanf("%s", input);
			if(isSingleDigit(input)){ //checks to make sure input is a single digit
				switch(input[0]) {
					case '0':
						//this will quit the program out of its main loop
						running = QUIT;
						break;
					case '1':
						//set action to sell moving program flow to that part of the switch statement
						action = SELL;
						break;
					default:
						//any other option at this point will just rerun the loop
						action = MAIN;
						break;
					}
			}
			break;
		//case to handle selling an item consists of three stages each with its own while loop START AMOUNT and CHANGE
		//START gets item's price, AMOUNT gets the amount paid, CHANGE tells you how much change is owed
		case SELL:
			while(sellAction == START){
				printPrompt(SELL);
				scanf("%s", input);
				if(isDollarFormat(input)){ //check that input is in acceptable format store in centsOwed and move to AMOUNT
					sellAction = AMOUNT;
					if(input[strlen(input)-1] == '.'){
						input[strlen(input)-1] = 0;
						centsOwed = toString(input)*100;
					}
					else if(input[strlen(input)-2] == '.'){
						input[strlen(input)-2] = input[strlen(input)-1];
						input[strlen(input)-1] = 0;
						centsOwed = toString(input)*10;
					}
					else if(input[strlen(input)-3] == '.'){
						input[strlen(input)-3] =input[strlen(input)-2];
						input[strlen(input)-2] = input[strlen(input)-1];
						input[strlen(input)-1] = 0;
						centsOwed = toString(input);
					}
					else{
						printf("unknown error\n");
					}
					
				}
			}
			while(sellAction == AMOUNT){

				printf("You are selling an item costing %d pennies\n", centsOwed);
				printf("How much are you being paid\n>>$");
				scanf("%s", input);
				if(isDollarFormat(input)){ //check format of input and make sure it is more than what is owed then move on to CHANGE
					if(input[strlen(input)-1] == '.'){
						input[strlen(input)-1] = 0;
						centsPaid = toString(input)*100;
						if(centsPaid >= centsOwed){
							sellAction = CHANGE;
						}
						else
							printf("Not enough money\n");
					}
					else if(input[strlen(input)-2] == '.'){
						input[strlen(input)-2] = input[strlen(input)-1];
						input[strlen(input)-1] = 0;
						centsPaid = toString(input)*10;
						if(centsPaid >= centsOwed){
							sellAction = CHANGE;
						}
						else
							printf("Not enough money\n");
					}
					else if(input[strlen(input)-3] == '.'){
						input[strlen(input)-3] =input[strlen(input)-2];
						input[strlen(input)-2] = input[strlen(input)-1];
						input[strlen(input)-1] = 0;
						centsPaid = toString(input);
						if(centsPaid >= centsOwed){
							sellAction = CHANGE;
						}
						else
							printf("Not enough money\n");
					}
					else{
						printf("unknown error\n");
					}
				}
			}
			while(sellAction == CHANGE){ //print out change owed and move program flow back to the main menu

				printf("your change is %d pennies\n", centsPaid - centsOwed);
				action = MAIN;
				sellAction = START;
			}
			
			break;
		}
	}
	return 0;
}