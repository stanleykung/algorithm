#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char filename[]="test.txt";
    FILE *fp;
    fp = fopen(filename,"r");
    if(fp == NULL){
        fputs ("File error",stderr); exit (1);
    }
        
    // obtain the file size
    fseek (fp , 0 , SEEK_END); // move the  position indicator to the file end
    int lSize = ftell (fp);
    rewind(fp); // re-point the indicator to beginning of the file
    printf("The file size of file: %d\n", lSize);

    // allocate memory to contain the whole file:
    char * buffer = malloc (sizeof(char)*lSize); //1338120
    if (buffer == NULL){
        fputs ("Memory error",stderr); exit (1);
    }

    //read the whole file
    fread(buffer,1,lSize,fp);
    for(int i = 0; i < 100000; i++){
        printf("%d, %c\t",i, buffer[i]);
    }
    return 0;
}