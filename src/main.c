//include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "Globals.h"
#include "Events/KeyEvents/CtrlC/CtrlC.h"
#include "Events/SafeExit/SafeExit.h"
#include "Output/DisplayContent/DisplayContent.h"
#include "Input/Tokenize/Tokenize.h"
#include "Input/InputHandler/InputHandler.h"

//initialization of globals
char* fileLocation;
char* content;
int shouldExit = 0;
int size = 0;
int jump = 0;
int foot = 0;

//main method
int main(int argc, char** argv){
    //set ctrl c signal
    signal(SIGINT, CtrlC);

    //check if location passed
    if (argc <= 1){
        //location not passed, error out
        printf("Error, no file passed");
        return 1;
    }

    //set file location
    fileLocation = argv[1];

    //load file into file pointer
    FILE* filePointer = fopen(argv[1], "rb");

    //check if file exists
    if (filePointer == NULL){
        printf("Cannot find %s: No such file", argv[1]);
        return 1;
    }

    //seek file size, store to size
    fseek(filePointer, 0 , SEEK_END);
    size = ftell(filePointer);

    //ensure size is a multiple of 16
    if (size % 16 != 0){
        printf("Error, missing data, size is not a multiple of 16");
        return 1;
    }

    //create content buffer with allocation of size + 1 -needed for end char-
    //read file into content buffer
    content = malloc(size+1);
    content[size] = '\0';
    fseek(filePointer, 0, SEEK_SET);
    fread(content, size, 1, filePointer);

    //close file for safety
    fclose(filePointer);

    //set jump and foot variables
    jump = 0;
    foot = size;

    //output file contents
    DisplayContent(content, size, jump, foot);

    //create input buffer of size 1024(64*16)
    //create token input buffer of size 1024(64*16)
    char inputBuffer[1024];
    char tokenInput[64][16];

    //input loop
    while (shouldExit == 0){
        //print line leader
        printf("Editor ~ ");

        //get input and push into input buffer
        fgets(inputBuffer, sizeof(inputBuffer), stdin);

        //tokenize input and store number of tokens
        int numTokens = Tokenize(inputBuffer, tokenInput, " ", 64, 16);

        //handle input
        InputHandler(tokenInput);

        //re-output file contents
        DisplayContent(content, size, jump, foot);
    }
    
    //return successful
    return 0;
}