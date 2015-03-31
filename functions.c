#include "functions.h"

int dollarsFromCents(int cents){
	return cents / 100;
}

int centsFromCents(int cents){
	return cents % 100;
}

void dollarFormat(int cents, char* output){
	if(centsFromCents(cents) < 10){
		sprintf(output, "$%d.0%d", dollarsFromCents(cents), centsFromCents(cents));
	}
	else{
		sprintf(output, "$%d.%d", dollarsFromCents(cents), centsFromCents(cents));
	}
}

int isSingleDigit(char input[]){
	if(input[0] > 47 && input[0] < 58){
		if(input[1] == 0){
			return 1;
		}
		else
			printf("error invalid selection\n");
		return 0;
	}
	else{
		printf("error invalid selection\n");
		return 0;
	}
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