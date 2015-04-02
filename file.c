#include "file.h"

int main(){
	
	addSKU(123,465, "sku.bin", "price.bin");
	//printf("%d\n", getTill("price.bin"));
	return 0;
}

void addSKU(int sku, int price, const char *skufile, const char *pricefile){
	FILE *sFile;
	FILE *pFile;
	int placeholder[] = {-1};
	int *buffer;
	int arrayLen = 0;
	int i;
	
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
		fread(buffer+i, sizeof(int), 1, pFile);
		printf("price element %d: %d\n", i+1, *(buffer+i));
	}
	rewind(pFile);	
	*(buffer+i) = price;
	*(buffer+i+1) = -1;
		
	fwrite(buffer, sizeof(int), arrayLen, pFile);
		
	
		
	for(i = 0; i < arrayLen - 2;i++){
		fread(buffer+i, sizeof(int), 1, sFile);
		printf("sku element %d: %d\n", i+1, *(buffer+i));
	}
	rewind(sFile);
	*(buffer+i) = sku;
	*(buffer+i+1) = -1;
		
	fwrite(buffer, sizeof(int), arrayLen, sFile);
		
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