#include "pos.h"

int main() {
	
	//variables
	char input[50];
	char cost[50];
	char change[50];
	char display[50];
	int intInput;
	int centsInTill = getTill("till.bin");
	int centsOwed;
	int centsPaid;
	int priceInput;
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
						
					case '2':
						//set action to adding money manually to the till
						action = ADDTILL;
						break;
						
					case '3':
						//set action to removing money manually from the till
						action = REMTILL;
						break;
						
					case '4':
						//set action to print out the balance of the till
						action = SHOWTILL;
						break;
						
					case '5':
						//set action to print out the list of skus and their prices
						action = PRINTSKU;
						break;
						
					case '6':
						//set action to add a sku and its price to the list
						action = ADDSKU;
						break;
						
					case '7':
						//set action to remove a sku and its price from the list
						action = REMSKU;
						break;
						
					case '8':
						//set action to find the price of a sku and print it
						action = SEEKPRICE;
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
				else {
					printf("input error\n");
					action = MAIN;
					break;
				}
			}
			
			while(sellAction == AMOUNT){
				
				dollarFormat(centsOwed, cost);
				
				printf("You are selling an item costing %s", cost);
				printf("\n");
				printf("How much are you being paid\n>>$");
				scanf("%s", input);
				
				if(isDollarFormat(input)){ //check format of input and make sure it is more than what is owed then move on to CHANGE
					if(input[strlen(input)-1] == '.'){
						input[strlen(input)-1] = 0;
						centsPaid = toString(input)*100;
						
						if(centsPaid >= centsOwed){
							sellAction = CHANGE;
						}
						
						else printf("Not enough money\n");
					}
					
					else if(input[strlen(input)-2] == '.'){
						input[strlen(input)-2] = input[strlen(input)-1];
						input[strlen(input)-1] = 0;
						centsPaid = toString(input)*10;
						
						if(centsPaid >= centsOwed){
							sellAction = CHANGE;
						}
						
						else printf("Not enough money\n");
					}
					
					else if(input[strlen(input)-3] == '.'){
						input[strlen(input)-3] =input[strlen(input)-2];
						input[strlen(input)-2] = input[strlen(input)-1];
						input[strlen(input)-1] = 0;
						centsPaid = toString(input);
						
						if(centsPaid >= centsOwed){
							sellAction = CHANGE;
						}
						
						else printf("Not enough money\n");
					}
					
					else{
						printf("unknown error\n");
					}
				}
				else{
					printf("input error\n");
					action = MAIN;
					break;
				}
			}
			
			while(sellAction == CHANGE){ //print out change owed and move program flow back to the main menu
				
				dollarFormat(centsPaid - centsOwed, change);
				addToTill(centsOwed, &centsInTill, "till.bin");
				
				printf("your change is %s\n", change);
				
				action = MAIN;
				sellAction = START;
			}
			break;
			
		case ADDTILL:
			printPrompt(ADDTILL);
			scanf("%s", input);
			
			if(isDollarFormat(input)){
				if(input[strlen(input)-1] == '.'){
					input[strlen(input)-1] = 0;
					
					addToTill(toString(input)*100, &centsInTill, "till.bin");
					
					action = MAIN;
				}
				
				else if(input[strlen(input)-2] == '.'){
					input[strlen(input)-2] = input[strlen(input)-1];
					input[strlen(input)-1] = 0;
					
					addToTill(toString(input)*10, &centsInTill, "till.bin");
					
					action = MAIN;
				}
				
				else if(input[strlen(input)-3] == '.'){
					input[strlen(input)-3] =input[strlen(input)-2];
					input[strlen(input)-2] = input[strlen(input)-1];
					input[strlen(input)-1] = 0;
					
					addToTill(toString(input), &centsInTill, "till.bin");
					
					action = MAIN;
				}
				
				else{
					printf("unknown error\n");
				}
			}
			else{
				printf("input error\n");
				action = MAIN;
			}
			break;
			
		case REMTILL:
			printPrompt(REMTILL);
			scanf("%s", input);
			
			if(isDollarFormat(input)){
				if(input[strlen(input)-1] == '.'){
					input[strlen(input)-1] = 0;
					
					if(centsInTill < toString(input)*100){
						printf("Not enough money\n");
					}
					
					else{
						addToTill(-1*toString(input)*100, &centsInTill, "till.bin");
						
						action = MAIN;
					}
				}
				
				else if(input[strlen(input)-2] == '.'){
					input[strlen(input)-2] = input[strlen(input)-1];
					input[strlen(input)-1] = 0;
					
					if(centsInTill < toString(input)*10){
						printf("Not enough money\n");
					}
					
					else{
						addToTill(-1*toString(input)*10, &centsInTill, "till.bin");
						
						action = MAIN;
					}
				}
				
				else if(input[strlen(input)-3] == '.'){
					input[strlen(input)-3] =input[strlen(input)-2];
					input[strlen(input)-2] = input[strlen(input)-1];
					input[strlen(input)-1] = 0;
					
					if(centsInTill < toString(input)){
						printf("Not enough money\n");
					}
					
					else{
						addToTill(-1*toString(input), &centsInTill, "till.bin");
						
						action = MAIN;
					}
				}
				
				else{
					printf("unknown error\n");
				}
			}
			else {
				printf("input error\n");
				action = MAIN;
			}
			break;
			
		case SHOWTILL:
			dollarFormat(centsInTill, display);
			printPrompt(SHOWTILL);
			printf("%s in it\n", display);
			
			action = MAIN;
			break;
			
		case PRINTSKU:
			printf("\n");
			printSKUS("sku.bin", "price.bin");
			printf("\n");
			
			action = MAIN;
			break;
			
		case ADDSKU:
			printPrompt(ADDSKU);
			scanf("%s", input);
			if(isPlainInt(input)){
				intInput = toString(input);
			}
			else{
				printf("input error\n");
				action = MAIN;
			}
			
			printf("What does SKU: %s cost?\n>>");
			scanf("%s", input);
			if(isDollarFormat(input)){
				if(input[strlen(input)-1] == '.'){
					input[strlen(input)-1] = 0;
					
					priceInput = toString(input)*100;
				}
				
				else if(input[strlen(input)-2] == '.'){
					input[strlen(input)-2] = input[strlen(input)-1];
					input[strlen(input)-1] = 0;
					
					priceInput = toString(input)*10;
					
				}
				
				else if(input[strlen(input)-3] == '.'){
					input[strlen(input)-3] =input[strlen(input)-2];
					input[strlen(input)-2] = input[strlen(input)-1];
					input[strlen(input)-1] = 0;
					
					priceInput = toString(input);
					
				}
				
				else{
					printf("unknown error\n");
					action = MAIN;
				}
			}
			else{
				printf("input error\n");
				action = MAIN;
				break;
			}
			
			addSKU(intInput, priceInput, "sku.bin", "price.bin");
			action = MAIN;
			break;
			
		case REMSKU:
			printPrompt(REMSKU);
			scanf("%s", input);
			if(isPlainInt(input)){
				remSKU(toString(input), "sku.bin", "price.bin");
			}
			else{
				printf("input error\n");
				action = MAIN;
				break;
			}
			action = MAIN;
			break;
		
		case SEEKPRICE:
			printPrompt(SEEKPRICE);
			scanf("%s", input);
			if(isPlainInt(input)){
				intInput = getPrice(toString(input), "sku.bin", "price.bin");
				if(intInput != 0){
					dollarFormat(intInput, display);
					printf("\nthe SKU %s costs %s\n\n", input, display);
					
				}
				action = MAIN;
				break;
			}
			else {
				printf("input error\n");
				action = MAIN;
				break;
				
			}
			
		}
	}
	
	return 0;
}