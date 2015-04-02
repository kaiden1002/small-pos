#include "file.h"

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