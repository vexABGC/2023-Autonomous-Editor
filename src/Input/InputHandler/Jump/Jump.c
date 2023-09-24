//includes
#include <stdlib.h>
#include "../../../Math/Max/Max.h"
#include "Jump.h"

//definition
void Jump(char tokenInput[64][16], int* jumpPointer){
    //get jump location address and set to jump variable
    *jumpPointer = strtol(tokenInput[1], NULL, 16);
    
    //ensure jump is 0 or more
    *jumpPointer = Max(*jumpPointer, 0);
}