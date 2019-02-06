#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1338120

int main(){
    char filename[]="ncku.txt";
    int buffer[SIZE];
    FILE *fp;
    fp = fopen(filename,"r");
    if(fp == NULL){
        fputs ("File error",stderr); exit (1);
    }

    //read the whole file
    int i=0;
    while(fscanf (fp, "%d, ", &buffer[i++]) != EOF){
        ;
    }
    //fread(buffer,1,lSize,fp);
    /*for(int i = SIZE-100; i < SIZE; i++){
        printf("%d\t",buffer[i]);
    }
    printf("\n");*/
    return 0;
}