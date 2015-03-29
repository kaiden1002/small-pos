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

int main() {
	char input[50];
	int i;
	int k = 0;
	int j = 0;
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
				k = 0;
				j = 0;
				if(input[0] > 48 && input[0] < 58){
					for(i = 1; input[i] != 0;i++){

						if(!(input[i] > 47 && input[i] < 58))
							k++;
						if(input[i] == '.')
							j++;
					}

					if(j == 1 && k == 1)
						sellAction = AMOUNT;
					else
						printf("input error try again.\n");
				}
				else
					printf("input error try again\n");
			}
			while(sellAction == AMOUNT){

				printf("You are selling an item costing $%s\n", input);
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

					if(j == 1 && k == 1)
						sellAction = CHANGE;
					else
						printf("input error try again.\n");
				}
				else
					printf("input error try again\n");
			}
			while(sellAction == CHANGE){

				printf("your change is \n");
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
