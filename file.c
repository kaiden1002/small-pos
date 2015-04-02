#include "file.h"
int main(void){
	
    int till = getTill("till.bin");
	printf("till is: %d\nchange to what\n>>", till);
	scanf("%d", &till);
	saveTill("till.bin", till);
	return 0;
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
	         
        exit(1);
    }
	
	fseek (pFile , 0 , SEEK_END);
    fileSize = ftell(pFile);
     
    rewind(pFile);
	     
	fread(&rValue, sizeof(int), fileSize, pFile);
    
	fclose(pFile);
	return rValue;
}