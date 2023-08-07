#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>								// add header file to include file error status

#define GPIO_NUMBER "4"
#define GPIO4_PATH "/sys/class/gpio/gpio4/"
#define GPIO_SYSFS "/sys/class/gpio/"

void writeGPIO(char filename[], char value[], char action[]){
	FILE *fp;									// create a file pointer fp
	int errnum;
	fp = fopen(filename, action);					// open file for write/update
	if(fp == NULL){
		errnum = errno;
      	fprintf(stderr, "Value of errno: %d\n", errno);
      	perror("Error printed by perror");
      	fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
      	fclose(fp);
		exit(1);
	}
	fprintf(fp, "%s", value);					// send the value to the file
	fclose(fp);									// close the file using fp
}

int main(int argc, char* argv[]){
	if (argc!=2){								// program name is argument 1
		printf("Usage is makeLED and one of:\n");
		printf("	setup, on, off, status or close.\n");
		printf(" e.g. makeLED on\n.");
		return 2;								//invalid number of arguments
	}
	printf("Starting the makeLED program.\n");
	if(strcmp(argv[1],"setup")==0){
		printf("Setting up the LED on the GPIO.\n");
		writeGPIO(GPIO_SYSFS "export", GPIO_NUMBER, "w");
		usleep(100000);							// sleep for 100ms
		writeGPIO(GPIO4_PATH "direction", "out", "w");
	}
	else if (strcmp(argv[1],"close")==0){
		printf("Closing the LED on the GPIO.\n");
		writeGPIO(GPIO_SYSFS "unexport", GPIO_NUMBER, "w");
	}
	else if (strcmp(argv[1],"on")==0){
		printf("Turning the LED on.\n");
		writeGPIO(GPIO4_PATH "value", "1", "w+");
	}
	else if (strcmp(argv[1],"off")==0){
		printf("Turning the LED off.\n");
		writeGPIO(GPIO4_PATH "value", "0", "w+");
	}
	else if (strcmp(argv[1],"status")==0){
		FILE* fp;						// see write GPIO above for description
		int read_errnum;
		char line[80], fullFilename[100];
		sprintf(fullFilename, GPIO4_PATH "/value");
		fp = fopen(fullFilename, "rt");	// reading text this time
		if(fp == NULL){
			read_errnum = errno;
      		fprintf(stderr, "Value of errno: %d\n", errno);
      		perror("Error printed by perror");
      		fprintf(stderr, "Error opening file: %s\n", strerror( read_errnum ));
      		fclose(fp);
			exit(1);
		}
		while (fgets(line, 80, fp) != NULL){
			printf("The state of the LED is %s", line);
		}
		fclose(fp);
	}
	else{
		printf("Invalid command.\n");
	}
	printf("Finished the makeLED program.\n");
	return 0;
}