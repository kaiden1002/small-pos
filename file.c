#include "file.h"

void printSKUS(const char *skufile, const char *pricefile){
	
	FILE *sFile;
	FILE *pFile;
	int *bufferOne;
	int *bufferTwo;
	int arrayLen = 0;
	int i;
	
	sFile = fopen(skufile, "rb+");
	pFile = fopen(pricefile, "rb+");
	
	if(sFile == NULL || pFile == NULL){
		perror("Error Occurred");
		printf("Error Code: %d\n", errno);
		exit(1);
	}

	for(;;){
		fread(&i, sizeof(int), 1, pFile);
		
		
		
		if(i == -1) break;
		
		arrayLen++;
	}

	rewind(pFile);
	
	bufferOne = (int*)malloc(sizeof(int)*arrayLen);
	bufferTwo = (int*)malloc(sizeof(int)*arrayLen);
	
	for(i = 0; i < arrayLen; i++){
		fread(bufferOne+i, sizeof(int), 1, sFile);
		fread(bufferTwo+i, sizeof(int), 1, pFile);
	}

	for(i = 0; i < arrayLen-1; i++){
		int buffOne = *(bufferOne+i);
		int buffTwo = *(bufferTwo+i);
		char price[50];
		
		dollarFormat(buffTwo, price);
		
		printf("SKU: %d costs %s\n", buffOne, price);
	}

	fclose(pFile);
	fclose(sFile);
	free(bufferOne);
	free(bufferTwo);
}

void remSKU(int sku, const char *skufile, const char *pricefile){
	
	FILE *sFile;
	FILE *pFile;
	int *buffer;
	int *final;
	int arrayLen = 0;
	int i;
	int j = 0;
	int skip = -2;
	
	sFile = fopen(skufile, "rb+");
	pFile = fopen(pricefile, "rb+");
	
	if(sFile == NULL || pFile == NULL){
		perror("Error Occurred");
		printf("Error Code: %d\n", errno);
		exit(1);
	}

	for(;;){
		fread(&i, sizeof(int), 1, pFile);
		
		
		
		if(i == -1) break;
		
		arrayLen++;
	}
	
	rewind(pFile);
	
	buffer = (int*)malloc(sizeof(int)*arrayLen);
	final = (int*)malloc(sizeof(int)*(arrayLen));	
		
	for(i = 0; i < arrayLen;i++){
		fread(buffer+i, sizeof(int), 1, sFile);
		
		if(*(buffer+i) == sku){
			skip = i;
		}
	}
	
	rewind(sFile);
	
	if(skip == -2 || skip == -1){
		printf("sku not found no removal\n");
	}
	
	else{
		for(i = 0; i < arrayLen; i++){
			if(skip != i){
				*(final+j) = *(buffer+i);
				printf("\n%d\n", *(final+j));
				j++;
			}
			
		}
		*(final+j) = -1;
		fwrite(final, sizeof(int), arrayLen-1, sFile);
		
		j = 0;
		
		for(i = 0; i < arrayLen; i++){
			fread(buffer+i, sizeof(int), 1, pFile);
		}
		rewind(pFile);
		
		for(i = 0; i < arrayLen; i++){
			if(skip != i){
				*(final+j) = *(buffer+i);
				printf("\n%d\n", *(final+j));
				j++;
			}
		}
		*(final+j) = -1;
		fwrite(final, sizeof(int), arrayLen-1, pFile);
	}
	
	fclose(sFile);
	fclose(pFile);
	free(buffer);
}

int getPrice(int sku, const char *skufile, const char *pricefile){
	
	int price = 0;
	FILE *sFile;
	FILE *pFile;
	int *buffer;
	int arrayLen = 0;
	int i;
	int location = -1;
	
	sFile = fopen(skufile, "rb");
	pFile = fopen(pricefile, "rb");
	
	if(sFile == NULL || pFile == NULL){
		perror("Error Occurred");
		printf("Error Code: %d\n", errno);
		exit(1);
	}
	
	for(;;){
		fread(&i, sizeof(int), 1, pFile);
		
		arrayLen++;
		
		if(i == -1) break;
	}
	
	rewind(pFile);
	
	buffer = (int*)malloc(sizeof(int)*arrayLen);
	
	for(i = 0; i < arrayLen - 1; i++){
		fread(buffer+i, sizeof(int), 1, sFile);
		
		if(*(buffer+i) == sku) location = i;
	}
	
	if(location == -1){
		printf("error sku not found\n");
	}
	
	for(i = 0; i < arrayLen - 1; i++){
		fread(buffer+i, sizeof(int), 1, pFile);
		
		if(i == location) price = *(buffer+i);
	}
	
	free(buffer);
	fclose(pFile);
	fclose(sFile);
	
	return price;
}

void addSKU(int sku, int price, const char *skufile, const char *pricefile){
	
	FILE *sFile;
	FILE *pFile;
	int placeholder[] = {-1};
	int *buffer;
	int arrayLen = 0;
	int i;
	int duplicate = 0;
	
	sFile = fopen(skufile, "rb+");
	pFile = fopen(pricefile, "rb+");
	
	if(sFile == NULL || pFile == NULL){
		perror("Error Occurred");
		printf("Error Code: %d\n", errno);
		printf("data files for sku library do not exist creating...\n");
		
		sFile = fopen(skufile, "wb+");
		pFile = fopen(pricefile, "wb+");
		
		if(sFile == NULL || pFile == NULL){
			perror("Error Occurred");
			printf("Error Code: %d\n", errno);
			exit(1);
		}
		
		fwrite(placeholder, sizeof(int), 1, pFile);
		fwrite(placeholder, sizeof(int), 1, sFile);
		rewind(pFile);
		rewind(sFile);
	}

	for(;;){
		fread(&i, sizeof(int), 1, pFile);
		
		arrayLen++;
		
		if(i == -1) break;
	}
	
	arrayLen++;
	
	rewind(pFile);
	
	buffer = (int*)malloc(sizeof(int)*arrayLen);	
		
	for(i = 0; i < arrayLen - 2;i++){
		fread(buffer+i, sizeof(int), 1, sFile);
		
		if(*(buffer+i) == sku){
			printf("duplicate sku error\nsku not added\n");
			
			duplicate = 1;
		}
	}
	
	rewind(sFile);
	
	*(buffer+i) = sku;
	*(buffer+i+1) = -1;
		
	if(!duplicate) fwrite(buffer, sizeof(int), arrayLen, sFile);
		
	for(i = 0; i < arrayLen - 2;i++){
		fread(buffer+i, sizeof(int), 1, pFile);
	}
	
	rewind(pFile);	
	
	*(buffer+i) = price;
	*(buffer+i+1) = -1;
		
	if(!duplicate) fwrite(buffer, sizeof(int), arrayLen, pFile);
	
	fclose(sFile);
	fclose(pFile);
	free(buffer);
}

void saveTill(const char *file, int till){
	
	FILE *pFile;
	pFile = fopen(file, "wb+");
	
    if(pFile == NULL){
        perror("Error Occurred");
		printf("Error Code: %d\n", errno);  
        exit(1);
    }
	
	fwrite(&till, sizeof(int), 1, pFile);
	fclose(pFile);
}

int getTill(const char *file){
	
	int rValue;
	FILE *pFile;
	pFile = fopen(file, "rb+");
	long fileSize;
	
    if(pFile == NULL){ 
        perror("Error Occurred");
		printf("Error Code: %d\n", errno);
	         
        printf("Till file does not exist creating...\n");
		
		saveTill(file, 0);
		
		return 0;
    }
	
	fseek (pFile , 0 , SEEK_END);
    
	fileSize = ftell(pFile);
     
    rewind(pFile);
	     
	fread(&rValue, sizeof(int), fileSize, pFile);
    
	fclose(pFile);
	return rValue;
}