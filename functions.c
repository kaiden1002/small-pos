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
		
		else printf("error invalid selection\n");
		
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
		printf("\nOptions:\n0. Quit Small POS\n");
		printf("1. Sell an item not in your SKU library\n");
		printf("2. Add to the till\n");
		printf("3. Remove from the till\n");
		printf("4. Show till balance\n");
		printf("5. Print List of SKUs\n");
		printf("6. Add to list of SKUs\n");
		printf("7. Remove from list of SKUs\n");
		printf("8. Find price of SKU\n");
		printf("9. Sell an item in your SKU library\n\n>>");
		break;
		
	case SELL:
		printf("\nPlease enter the item you wish to sell's price\n");
		printf("(use the format 0.00)\n\n>>$");
		break;
		
	case ADDTILL:
		printf("\nHow much to add to the till?\n");
		printf("(use the format 0.00)\n\n>>$");
		break;
		
	case REMTILL:
		printf("\nHow much to remove from the till?\n(use the format 0.00)\n\n>>$");
		break;
		
	case SHOWTILL:
		printf("\nThe till has ");
		break;
		
	case ADDSKU:
		printf("\nWhat number SKU would you like to add?\n\n>>");
		break;
		
	case REMSKU:
		printf("\nWhich SKU to remove?\n\n>>");
		break;
	
	case SEEKPRICE:
		printf("\nWhat SKU would you like to look up?\n\n>>");
		break;
	case SKUSELL:
		printf("\nWhat SKU would you like to sell?\n\n>>");
		break;
		
	default:
		break;
	}
}

void addToTill(int amount, int* till, const char *file){
	
	*till += amount;
	
	saveTill("till.bin",*till);
}

int isDollarFormat(char input[]) {
	
	int k = 0;
	int j = 0;
	int i;
	
	if(input[0] > 47 && input[0] < 58){
		for(i = 1; input[i] != 0;i++){
			if(!(input[i] > 47 && input[i] < 58)) k++;
			if(input[i] == '.') j++;
		}

		if(j == 1 && k == 1){
			for(i = 0; input[i] != 0; i++){}
			
			if(!(input[i-1] == '.' || input[i-2] == '.' || input[i-3] == '.')){
				printf("input error\n");
				
				return 0;
			}
			
			else return 1;			
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

int isPlainInt(char *input){
	
	int r = 1;
	int i;
	
	for(i = 0; *(input+i) != 0; i++){
		if(!(*(input+i) > 47 && *(input+i) < 58)){
			r = 0;
		}
	}
	
	return r;
}

int toString(char a[]){
	
	int c;
	int sign;
	int offset;
	int n;
 
	if (a[0] == '-'){
		sign = -1;
	}
	
	if (sign == -1){
		offset = 1;
	}
	
	else{
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