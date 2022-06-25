#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Position{
	int X;
	int Y;
};

int main(void){

	FILE* fp;
	char commands[32];

	fp = fopen("./data.txt", "r");

	struct Position Sub;
	Sub.Y = 0; Sub.X = 0;

	while(fgets(commands, 32, fp) != NULL){

		char direction[10];
		int units;

		const char delim[2] = " ";
		char* command = strtok(commands, delim);

		int counter = 0;
		while(command != NULL){

			if (counter == 0){ strcpy(direction, command);} 
			else { units = atoi(command); }

			command = strtok(NULL, delim);
			counter++;
		}

		if (!strcmp(direction, "up")){
			Sub.Y -= units;
		}
		else if (!strcmp(direction, "down")){
			Sub.Y += units;
		}
		else if (!strcmp(direction, "forward")){
			Sub.X += units;
		}

	}

	printf("%d\n", Sub.Y*Sub.X);

	return 0;
}