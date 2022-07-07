#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

int index;    
int bufflen = 1;

int filtercmp(int * filter, char buff[])
{
    if (index == 0) { return 0; }

    int isEqual = 1;    
    int i;
    for (i = index-1; i >= 0; i--) {
        if (!strcmp(atoi(buff[i]), filter[i])){
            isEqual = 0;
        }
    }
    return isEqual;
}

int binaryToDecimal(int * binary)
{
    int decNumber = 0;
    int i;
    for (i = 0; i < bufflen; i++)
    {
        if(binary[i] == 1)
        {
            decNumber += pow(2, (bufflen-1) - i);
        }       
    }
    return decNumber;
}


int main(void)
{

    FILE* fp;
    char buff[64];
    int oxygenCount;
    int co2Count;
    int* oxygenGen;
    int* CO2scrubb;

    fp = fopen("../data.txt", "r");
    if (fp == NULL)
    { printf("Error: Could not open data file\n"); }

    int completed;
    int allocatedArray;
    while(!completed)
    {
        oxygenCount = 0;
        co2Count = 0;
        while(fgets(buff, sizeof(buff), fp) != NULL){
            if(!allocatedArray)
            {
                int bufflen = strlen(buff);
                oxygenGen = (int *) malloc(bufflen * sizeof(int));
                CO2scrubb = (int *) malloc(bufflen * sizeof(int));
                allocatedArray = 1;
            }

            if (index == 0){
                if (buff[index] == '1')
                {
                    co2Count += 1;
                    oxygenCount += 1;
                } else if (buff[index] == '0'){
                    co2Count -= 1;
                    oxygenCount -= 1;
                }
            }

            if (filtercmp(oxygenGen, buff))
            {
                if (buff[index] == '1')
                {
                    oxygenCount += 1;
                } else if (buff[index] == '0'){
                    oxygenCount -= 1;
                }
            } else if (filtercmp(CO2scrubb, buff)){

                if (buff[index] == '1')
                {
                    co2Count += 1;
                } else if (buff[index] == '0'){
                    co2Count -= 1;
                }
            }
            

        }

        if (oxygenCount >= 0){
            oxygenGen[index] = 1;
        } else {
            oxygenGen[index] = 0;
        }

        if (co2Count < 0){
            oxygenGen[index] = 1;
        } else {
            oxygenGen[index] = 0; 
        }

        if (index  == bufflen - 1){
            completed = 1;
        } else {
            index++;
        }
    }

    free(oxygenGen);
    free(CO2scrubb);
    

    return 0;
}