//includes
#include <stdlib.h>
#include "../../../Math/Min/Min.h"
#include "Foot.h"

//definition
void Foot(char tokenInput[64][16], int* footPointer, int size){
    //get foot location address and set to foot variable
    *footPointer = strtol(tokenInput[1], NULL, 16);
    
    //ensure jump is less than size + 1
    *footPointer = Min(*footPointer, size+1);
}