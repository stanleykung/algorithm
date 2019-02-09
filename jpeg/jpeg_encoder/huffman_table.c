#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){
    const char * luminance_DC_Huff[3]={"00","010","111111110"};
    printf("%s\n",luminance_DC_Huff[1]);
    return 0;
}