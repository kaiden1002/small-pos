#include <stdio.h>
#include <string.h>
#define SELL 12
#define MAIN 10
#define QUIT 0
#define RUN 1
#define START 56
#define AMOUNT 43
#define CHANGE 31

void printPrompt(int prompt);
int toString(char a[]);
int isDollarFormat(char input[]);

int main() {
	char input[50];
	int i;
	int k = 0;
	int j = 0;
	int centsOwed;
	int centsPaid;
	int centsChange;
	int running = RUN;
	int action = MAIN;
	int sellAction = START;
	while(running) {

		switch(action){

		case MAIN:
			printPrompt(MAIN);
			scanf("%s", input);
			if(input[0] > 47 && input[0] < 58){
				if(input[1] == 0){
					switch(input[0]) {

					case '0':
						running = QUIT;
						break;
					case '1':
						action = SELL;
						break;
					default:
						action = MAIN;
						break;
					}
				}
				else
					printf("error invalid selection\n");
			}
			else
				printf("error invalid selection\n");
			break;
		case SELL:
			while(sellAction == START){
				printPrompt(SELL);
				scanf("%s", input);
				if(isDollarFormat(input)){
					sellAction = AMOUNT;
					if(input[strlen(input)-1] == '.'){
						input[strlen(input)-1] = 0;
					}
					else if(input[strlen(input)-2] == '.'){
						input[strlen(input)-2] = input[strlen(input)-1];
						input[strlen(input)-1] = 0;
					}
					else if(input[strlen(input)-3] == '.'){
						input[strlen(input)-3] =input[strlen(input)-2];
						input[strlen(input)-2] = input[strlen(input)-1];
						input[strlen(input)-1] = 0;
					}
					else{
						printf("unknown error\n");
					}
					centsOwed = toString(input);
				}
			}
			while(sellAction == AMOUNT){

				printf("You are selling an item costing %d pennies\n", centsOwed);
				printf("How much are you being paid\n>>$");
				scanf("%s", input);
				k = 0;
				j = 0;
				if(input[0] > 48 && input[0] < 58){
					for(i = 1; input[i] != 0;i++){

						if(!(input[i] > 47 && input[i] < 58))
							k++;
						if(input[i] == '.')
							j++;
					}

					if(j == 1 && k == 1){
						centsPaid = 0;
						for(i = 0; input[i] != 0; i++){}
						if(input[i-1] == '.')
						{
							sellAction = CHANGE;
							input[i-1] = 0;
							centsPaid += (toString(input)*100);
							
						}
						else if(input[i-2] == '.')
						{
							sellAction = CHANGE;
							input[i-2] = 0;
							centsPaid += ((input[i-1] - 48) * 10)+(toString(input)*100);
						}
						else if(input[i-3] == '.')
						{
							sellAction = CHANGE;
							input[i-3] = 0;
							centsPaid += (input[i-1] - 48)+((input[i-2] - 48) * 10)+(toString(input)*100);
						}
						else
							printf("input error\n");
						
					}
					else
						printf("input error try again.\n");
				}
				else
					printf("input error try again\n");
			}
			while(sellAction == CHANGE){

				printf("your change is %d pennies\n", centsPaid - centsOwed);
				action = MAIN;
				sellAction = START;
			}
			
			break;
		}
	}
	return 0;

}

void printPrompt(int prompt) {

	switch(prompt) {

	case MAIN:
		printf("Welcome to Small POS\n");
		printf("What Would You Like To Do?\n");
		printf("Options:\n0. Quit Small POS\n");
		printf("1. Sell an item\n");
		printf("2. \n");
		printf("3. \n");
		printf("4. \n");
		printf("5. \n");
		printf("6. \n");
		printf("7. \n");
		printf("8. \n");
		printf("9. \n>>");
		break;
	case SELL:
		printf("Please enter the item you wish to sell's price\n");
		printf("(use the format 0.00)\n>>$");
		break;
	default:
		break;

	}

}

int isDollarFormat(char input[]) {
	
	int k = 0;
	int j = 0;
	int i;
	if(input[0] > 48 && input[0] < 58){
		for(i = 1; input[i] != 0;i++){

			if(!(input[i] > 47 && input[i] < 58))
				k++;
			if(input[i] == '.')
				j++;
		}

		if(j == 1 && k == 1){
			for(i = 0; input[i] != 0; i++){}
			if(!(input[i-1] == '.' || input[i-2] == '.' || input[i-3] == '.')){
				printf("input error\n");
				return 0;
			}
			else{
				return 1;
			}			
		}	
		else{
			printf("input error try again.\n");
			return 0;
		}
	}
	else{
		printf("input error try again\n");
		return 0;
	}
	
}

int toString(char a[]) {
	int c, sign, offset, n;
 
	if (a[0] == '-') 
	{
		sign = -1;
	}
	if (sign == -1) 
	{
		offset = 1;
	}
	else 
	{
		offset = 0;
	}
 
	n = 0;
 
	for (c = offset; a[c] != '\0'; c++) {
		n = n * 10 + a[c] - '0';
	}
 
	if (sign == -1) {
		n = -n;
	}
 
	return n;
}
