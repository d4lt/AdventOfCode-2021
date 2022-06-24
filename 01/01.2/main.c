#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct Sample{

	int a;
	int b;
	int c;
};

int ssum(struct Sample* samp){
	int sum = samp->a + samp->b + samp->c;
	return sum; 
}

int main(void){

	FILE* fptr;
	char buff[64];
	int counter = 0;

	fptr = fopen("../data.txt", "r");

    if (NULL == fptr){
    	printf("unable to read file");
    	exit(1);
    };

	int components[3];
	
	int i = 0;
	while(fgets(buff ,64, fptr) != NULL && i < 3){
		int component = atoi(buff);
		components[i] = component;
		i += 1;
	}
	struct Sample A;
	A.a = components[0]; A.b = components[1]; A.c = components[2];

    while(!feof(fptr)){

		int B_c;
		if(fgets(buff,16,fptr ) != NULL){

		B_c = atoi(buff);
		} else {
			
			break; 
		}

		struct Sample B;
		B.a = A.b; B.b = A.c; B.c = B_c;

		if(ssum(&A) < ssum(&B)) { counter += 1;}

		A = B;

	}	
    printf("%i\n", counter);

	fclose(fptr);
	return 0;
}