#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int buffLen;


int binaryToDecimal(int * binary)
{
    int decNumber = 0;
    int i;
    for (i = 0; i < buffLen; i++)
    {
        if(binary[i] == 1)
        {
            decNumber += pow(2, (buffLen-1) - i);
        }       
    }
    return decNumber;
}


int main(void)
{

    FILE* fp;
    char buff[64];
    int* bitArray;
    int* gammaRate;
    int* epsilonRate;

    fp = fopen("../data.txt", "r");
    if (fp == NULL)
    {
        printf("Error: Could not open data file\n");

    }

    int allocatedArray = 0; // if the bit array is already created
    while( fgets(buff, sizeof(buff), fp) != NULL )
    {
        if(!allocatedArray)
        {
            buffLen = strlen(buff) - 1;
            bitArray = (int *) calloc(buffLen, sizeof(int));
            if (bitArray == NULL){
                printf("Error: Failed to allocate bit array\n");
                exit(1);
            }
            allocatedArray = 1;
        }

        int i;
        for(i = 0; i < buffLen; i++)
        {
            if (buff[i] == '1')
            {
                bitArray[i] += 1;
            } 
            else if (buff[i] == '0')
            {
                bitArray[i] -= 1;
            }
        }
    }

    gammaRate = (int *) malloc(sizeof(int)*buffLen);
    if(gammaRate == NULL)
    {
        printf("Error: Failed to allocate gammaRate");
        exit(1);
    }

    int j;
    for(j = 0; j < buffLen; j++)
    {
        if (bitArray[j] < 0)
        {
            gammaRate[j] = 0;
        }
        else if (bitArray > 0)
        {
            gammaRate[j] = 1;
        }
    }  

    epsilonRate = (int *) malloc(sizeof(int) * buffLen);
    if(epsilonRate == NULL)
    {
        printf("Error: Failed to allocate epsilonRate");
        exit(1);
    }

    int k;
    for(k=0; k < buffLen; k++)
    {
        if (gammaRate[k] == 1)
        {
            epsilonRate[k] = 0;
        } else if (gammaRate[k] == 0)
        {
            epsilonRate[k] = 1;
        }
    }

    int decimalGamma = binaryToDecimal(gammaRate);
    int decimalEpsilon = binaryToDecimal(epsilonRate);


    printf("\ngamma = %d, epsilon = %d, power consumption = %d\n", decimalGamma, decimalEpsilon, 
    decimalGamma * decimalEpsilon);

    free(bitArray);
    free(gammaRate);
    free(epsilonRate);

    return 0;
}