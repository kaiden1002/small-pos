#include "file.h"
int main(void){
	 
    FILE *pFile;
	     
    // Holds the data retrieved from the file
     
    char * buffer;
	     
    // size_t is a data type used to represent the size
    // of an element in bytes. 10 chars would be equal
    // to a size of 11 for example.
	     
    size_t dataInFile;
	     
	// Will hold the size of the file
     
    long fileSize;
	 
    // Opens the file using binary mode
	 
    pFile = fopen("test.bin", "rb+");
	     
    // If the file doesn't exist we will produce errors
    // and then try to create the file
	     
    if(pFile == NULL){
	     
        // Prints the string provided followed by the
        // standard error message and assign an error
        // code to the variable errno
	     
        perror("Error Occurred");
		printf("Error Code: %d\n", errno);
	         
        printf("File Being Created\n\n");
        
        // Create the file
	         
        pFile = fopen("test.bin", "wb+");
	         
        if(pFile == NULL){
	         
            perror("Error Occurred");
            printf("Error Code: %d\n", errno);
            exit(1);
	         
        }
	     
    }
	 
	char name[] = "Hello BIN";
	 
    // fwrite() writes binary data to a file
    // You pass a pointer to what to write to the file.
    // Then the size of each element in the array for example,
    // or if you are righting a struct sizeof(theStruct).
    // The 3rd is the number of elements to write of the type
    // specified. Finally list the file pointer
	 
    fwrite(name, sizeof(name[0]), sizeof(name)/sizeof(name[0]), pFile);
	     
    // Go to the end of the file with fseek(), so I can use
    // ftell() to get the file size
	     
    fseek (pFile , 0 , SEEK_END);
    fileSize = ftell(pFile);
	     
    // Set pointer back to the beginning of the file
     
    rewind(pFile);
	     
    // Set aside enough space in memory to hold the file
	     
    buffer = (char*) malloc (sizeof(char)*fileSize);
	     
    if(buffer == NULL){
     
        perror("Error Occurred");
        printf("Error Code: %d\n", errno);
        exit(2);
	     
    }
	     
    // fread() reads data from the file provided into the
    // buffer provided. The 2nd attribute is the number
    // of bytes taken up by each element read. The 3rd
    // attribute is the number of elements to read.
	     
    // fread() returns a size_t equal to the amount of
    // bytes stored in the file.
	     
    dataInFile = fread(buffer, 1, fileSize, pFile);
	     
    if(dataInFile != fileSize){
	     
        perror("Error Occurred");
        printf("Error Code: %d\n", errno);
        exit(3);
	     
    }
	     
    printf("%s\n", buffer);
	     
    printf("\n");
     
    // Closes the file associated with the stream
	     
    fclose(pFile);
	     
    // Deallocates the memory block created for the buffer
	     
    free(buffer); 
	return 0;
}