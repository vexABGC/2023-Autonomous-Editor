//include
#include <string.h>
#include "Tokenize.h"

//definition
int Tokenize(char* content, char tokenedOutput[64][16], char* delimiter, int numTokens, int tokenSize){
    int count = 0;
    char* token = strtok(content, delimiter);
    while (token != NULL && count < numTokens){
        strncpy(tokenedOutput[count], token, tokenSize);
        count += 1;
        token = strtok(NULL, delimiter);
    }
    return count;
}