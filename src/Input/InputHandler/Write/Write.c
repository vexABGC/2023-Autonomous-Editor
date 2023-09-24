//includes
#include <stdio.h>
#include <stdlib.h>
#include "Write.h"

//definition
void Write(char* content, char chunkedInput[64][16]){
    //get lower address line
    int lowerAddr = strtol(chunkedInput[1], NULL, 16);

    //get upper address line
    int upperAddr = strtol(chunkedInput[2], NULL, 16);

    //get lower byte
    int lowerByte = atoi(chunkedInput[3]);

    //get upper byte
    int upperByte = atoi(chunkedInput[4]);

    //get line and data size
    int lineSize = upperAddr - lowerAddr;
    int dataSize = upperByte - lowerAddr;

    //get data and store to data array
    int* data = malloc(dataSize);
    for (int i = 0; i < dataSize; i++){
        sscanf(chunkedInput[5+i], "%hhd", &(data[i]));
    }

    //write data
    for (int line = 0; line < lineSize; line++){
        for (int byte = 0; byte < dataSize; byte++){
            int location = (lowerAddr+line)*16+lowerByte+byte;
            content[location] = data[byte];
        }
    }
}