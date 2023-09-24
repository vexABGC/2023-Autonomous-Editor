//includes
#include <stdio.h>
#include "Save.h"

//definition
void Save(char* location, char* content, int size){
    //open file
    FILE* fp = fopen(location, "wb");

    //write data to file
    fwrite(content, size, 1, fp);

    //close file
    fclose(fp);

    //respond to input
    printf("Saved to file\n");
}