//include
#include <stdio.h>
#include "DisplayContent.h"

//definition
void DisplayContent(char* content, int size, int jump, int foot){
    //display header
    printf("      LA_X LA_Y RA_X RA_Y D_UP D_DW D_LF D_RH D_BA D_BB D_BX D_BY D_L1 D_L2 D_R1 D_R2\n");

    //loop through each line of content
    //one line for every 16 bytes
    for (int line = 0; line < (int)((foot-jump)/16); line++){
        //print line address
        printf("$%04x ", line*16+jump);

        //loop through each byte of line
        for (int byte = 0; byte < 16; byte++){
            //get value in int8 form
            __int8 value = (__int8) content[line*16+byte];

            //print value with leading sign(special manipulation for positive)
            if (value >= 0){
                printf("+%03i ", value);
            }else{
                printf("%04i ", value);
            }
        }

        //create new line
        printf("\n");
    }
}