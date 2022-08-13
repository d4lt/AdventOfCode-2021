#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define BUFFER_SIZE 64
#define CHAR2INT_NUMBER 48

int bufflen = 0;

int filtercmp(int * filter, char buff[], int index)
{

    if (index == 0) { return 0; }

    int isEqual = 1;    
    for (int i = 0; i < index; ++i) {
        if ( (int )(buff[i]) - CHAR2INT_NUMBER != filter[i] ) {
            isEqual = 0;
        }
    }

    return isEqual;
}


int binaryToDecimal(char binary[])
{
    int decNumber = 0;
    for (int i = 0; i < bufflen; ++i) {
        if (binary[i] == '1') {
            decNumber += pow(2,bufflen-1 - i);
        }  
    }

    return decNumber;
}


int main(void)
{

    FILE* fp;
    char buff[BUFFER_SIZE];

    char oxygenGen[BUFFER_SIZE];
    char co2scrub[BUFFER_SIZE];

    int oxygenCount, co2Count;

    int* oxygen_filter;
    int* co2_filter;

    int index = 0;

    fp = fopen("../data.txt", "r");
    if (fp == NULL)
    { printf("Error: Could not open data file\n"); exit(1);}

    int completed = 0;
    int allocatedArray = 0;

    int o2buff_count = 0;
    int co2buff_count = 0;
    int found_o2 = 0;
    int found_co2 = 0;

    while(!completed)
    {

        o2buff_count = 0;
        co2buff_count = 0;
        
        oxygenCount = 0;
        co2Count = 0;

        while( fgets(buff, BUFFER_SIZE, fp) != NULL )
        {

            if(!allocatedArray)
            {
                bufflen = strlen(buff) - 1;
                oxygen_filter = (int *) malloc(bufflen * sizeof(int));
                co2_filter = (int *) malloc(bufflen * sizeof(int));
                allocatedArray = 1;
            }

            if (index == 0){
                if (buff[0] == '1'){
                    co2Count += 1;
                    oxygenCount += 1;

                } else if (buff[0] == '0'){
                    co2Count -= 1;
                    oxygenCount -= 1;
                }
            } 

            if ( filtercmp(oxygen_filter, buff, index) ){

                if (buff[index] == '1')
                {
                    oxygenCount += 1;
                } else if (buff[index] == '0'){
                    oxygenCount -= 1;
                }
                
                if (!found_o2){
                    strcpy(oxygenGen, buff);
                    o2buff_count += 1;
                }
            }

            if ( filtercmp(co2_filter, buff, index) ){

                if (buff[index] == '1')
                {
                    co2Count += 1;
                } else if (buff[index] == '0'){
                    co2Count -= 1;
                }

                if (!found_co2){
                    strcpy(co2scrub, buff);
                    co2buff_count += 1;
                }
            }
        }

        if (oxygenCount >= 0){
            oxygen_filter[index] = 1;
        } else {
            oxygen_filter[index] = 0;
        }

        if (co2Count >= 0){
            co2_filter[index] = 0;
        } else if ( co2Count < 0 ) {
            co2_filter[index] = 1;  
        }

        if (o2buff_count == 1){
            found_o2 = 1;
        }
        if (co2buff_count == 1){
            found_co2 = 1;
        }

        if ( fseek(fp, 0L, SEEK_SET) != 0 ){
            printf("failed to rewind file\n");
            exit(1);
        }

        if (index  == bufflen -1){
            completed = 1;

        } else {
            index++;
        }
       
    }

    fclose(fp); 

    printf("bufflen: %d\n", bufflen);
    printf("indexes: %d\n", index);
    
    printf("binary oxygen generator: %s\n", oxygenGen);
    printf("binary co2 scrubber generator: %s\n", co2scrub);


    int decimal_oxygen = binaryToDecimal(oxygenGen);
    int decimal_CO2 = binaryToDecimal(co2scrub);

    printf("decimal oxygen: %d\n", decimal_oxygen);
    printf("decimal CO2: %d\n", decimal_CO2);

    printf("life support: %d\n", decimal_oxygen*decimal_CO2);

    free(oxygen_filter);
    free(co2_filter);
    

    return 0;
}