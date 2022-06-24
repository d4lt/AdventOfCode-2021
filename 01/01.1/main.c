#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void){
	FILE* fptr;
	char buff[64];

	int counter = 0;
	int prev_depth = 0;
	int depth;

	fptr = fopen("../data.txt", "r");

    if (NULL == fptr){
    	printf("unable to read file");
    	exit(1);
    };

    while(fgets(buff,64,fptr) != NULL){

    	depth = atoi(buff);


    	if (depth > prev_depth && prev_depth != 0){
		counter += 1;
		}

		prev_depth = depth;
    }

    printf("%i\n", counter);

	return 0;
}