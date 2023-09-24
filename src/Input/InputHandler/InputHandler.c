//include
#include <stdio.h>
#include <string.h>
#include "../../Globals.h"
#include "InputHandler.h"
#include "Save/Save.h"
#include "Write/Write.h"
#include "Jump/Jump.h"
#include "Foot/Foot.h"

//definition
void InputHandler(char tokenInput[64][16]){
    //command hand selection and hand off
    if(strcmp(tokenInput[0], "save\n") == 0){
        Save(fileLocation, content, size);
    }else if(strcmp(tokenInput[0], "write") == 0){
        Write(content, tokenInput);
    }else if(strcmp(tokenInput[0], "jump") == 0){
        Jump(tokenInput, &jump);
    }else if(strcmp(tokenInput[0], "foot") == 0){
        Foot(tokenInput, &foot, size+1);
    }else{
        printf("Invalid command\n");
    }
}