//includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>

//globals
int exitFlag = 0;

//methods
int countInstances(char* string, char character){
    int count = 0;
    for (int i = 0; i < sizeof(string)/sizeof(char); i++){
        if (string[i] == character){
            count += 1;
        }
    }
    return count;
}

int lowerNum(int a, int b){
    if (a < b){
        return a;
    }
    return b;
}

int higherNum(int a, int b){
    if (a > b){
        return a;
    }
    return b;
}

void ctrlC(){
    //set exit flag
    exitFlag = 1;
}

//main
int main(int argc, char** argv) {
    //setup ctrl c closing
    signal(SIGINT, ctrlC);

    //check if location passed
    if (argc <= 1){
        //location not passed, error out
        printf("Error, no file passed");
        return 1;
    }

    //load file
    FILE* filePointer;
    filePointer = fopen(argv[1], "rb");
    
    //check if file exists
    if (filePointer == NULL){
        printf("Cannot find %s: No such file", argv[1]);
        return 1;
    }

    //get file size
    fseek(filePointer, 0, SEEK_END);
    int size = ftell(filePointer);

    //check file size
    if (size % 16 != 0){
        printf("Error, missing data, size is not a multiple of 16");
        return 1;
    }

    //read file into char buffer
    char* fileBuffer = malloc(size+1);
    fileBuffer[size] = '\0';
    fseek(filePointer, 0, SEEK_SET);
    fread(fileBuffer, size, 1, filePointer);

    //close file
    fclose(filePointer);

    //output file contents
    //print header
    printf("      LA_X LA_Y RA_X RA_Y D_UP D_DW D_LF D_RH D_BA D_BB D_BX D_BY D_L1 D_L2 D_R1 D_R2\n");
    //print each line
    for (int line = 0; line < (int)(size/16); line++){
        //print address
        printf("$%04x ", line*16);

        //print bytes
        for (int byteIndex = 0; byteIndex < 16; byteIndex++){
            //get value
            __int8 value = (__int8)fileBuffer[line*16 + byteIndex];

            //print sign
            if (value >= 0){
                printf("+");
            }
            else{
                printf("-");
            }

            //print absolute of int 8 value
            printf("%03i ",abs(value));
        }

        //print new line
        printf("\n");
    }

    //create input buffer
    char inputBuffer[256];

    //loop globals
    int jump = 0;
    int foot = size;

    //user input loop
    while (1){
        //print line lead
        printf("Editor ~ ");

        //get input
        fgets(inputBuffer, sizeof(inputBuffer), stdin);

        //create chunk buffer
        char chunkedInput[64][16];

        //chunk up
        int count = 0;
        char* token = strtok(inputBuffer, " ");
        while(token != NULL){
            strncpy(chunkedInput[count], token, 16);
            count += 1;
            token = strtok(NULL, " ");
        }
        
        //command operations
        if(strcmp(chunkedInput[0], "write") == 0){
            //get lower address line
            int lowAddress = (int)strtol(chunkedInput[1], NULL, 16);
            //get upper address line
            int highAddress = (int)strtol(chunkedInput[2], NULL, 16);
            //get lower byte
            int lowByte = atoi(chunkedInput[3]);
            //get upper byte          
            int highByte = atoi(chunkedInput[4]);
            //get data
            int lineSize = highAddress - lowAddress;
            int dataSize = highByte-lowByte;
            int* data = malloc(dataSize);
            for (int i = 0; i < dataSize; i++){
                sscanf(chunkedInput[5+i], "%hhd", &(data[i]));
            }
            //execute command
            for (int line = 0; line < lineSize; line++){
                for (int byte = 0; byte < dataSize; byte++){
                    fileBuffer[(lowAddress+line)*16 + lowByte + byte] = data[byte];
                }
            }
        }else if(strcmp(chunkedInput[0], "save") == 0 || strcmp(chunkedInput[0], "save\n") == 0){
            //open file
            filePointer = fopen(argv[1], "wb");
            //write data to file
            fwrite(fileBuffer, size, 1, filePointer);
            //close file
            fclose(filePointer);
            //respond to input
            printf("Saved to file\n");
        }else if(strcmp(chunkedInput[0], "jump") == 0){
            //get jump location address and set to jump, ensure is now lower than 0
            jump = higherNum((int)strtol(chunkedInput[1], NULL, 16),0);
            //respond to input
            printf("Jumped\n");
        }else if(strcmp(chunkedInput[0], "foot") == 0){
            //get foot location address and set to foot, ensure is lower than size + 1
            foot = lowerNum((int)strtol(chunkedInput[1], NULL, 16),size+1);
            //respond to input
            printf("Set foot\n");
        }else if(chunkedInput[0][0] == 'q' || strcmp(chunkedInput[0], "exit\n") == 0){
            //q or exit typed, exit
            return 0;
        }else{
            printf("Invalid command\n");
        }

        //check for exit flag
        if(exitFlag){
            return 0;
        }

        //output file contents
        //print header
        printf("      LA_X LA_Y RA_X RA_Y D_UP D_DW D_LF D_RH D_BA D_BB D_BX D_BY D_L1 D_L2 D_R1 D_R2\n");
        //print each line
        for (int line = 0; line < (int)((foot-jump)/16); line++){
            //print address
            printf("$%04x ", line*16 + jump);

            //print bytes
            for (int byteIndex = 0; byteIndex < 16; byteIndex++){
                //get value
                __int8 value = (__int8)fileBuffer[line*16 + jump + byteIndex];

                //print sign
                if (value >= 0){
                    printf("+");
                }
                else{
                    printf("-");
                }

                //print absolute of int 8 value
                printf("%03i ",abs(value));
            }

            //print new line
            printf("\n");
        }
    }
}