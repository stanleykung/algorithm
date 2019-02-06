#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 826
#define HEIGHT 540
#define CHANNEL 3
#define SIZE WIDTH*HEIGHT*CHANNEL

int main(){
    //char filename[]=;
    FILE *fp;
    fp = fopen("/home/kungdehan/program_practice/github/algorithm/jpeg/jpeg_encoder/ncku.txt","r");
    if(fp == NULL){
        fputs ("File error",stderr); exit (1);
    }

    float * buffer = malloc(sizeof(float)*SIZE);
    float * R = malloc(sizeof(float)*WIDTH*HEIGHT);
    float * G = malloc(sizeof(float)*WIDTH*HEIGHT);
    float * B = malloc(sizeof(float)*WIDTH*HEIGHT);
    float * Y_ = malloc(sizeof(float)*WIDTH*HEIGHT);
    float * Cb = malloc(sizeof(float)*WIDTH*HEIGHT);
    float * Cr = malloc(sizeof(float)*WIDTH*HEIGHT);

    //read the whole file
    int count=0;
    while(fscanf(fp, "%f, ", &buffer[count++]) != EOF){
        ;
    }
    fclose(fp);
    //fread(buffer,1,lSize,fp);
    /*for(int i = 0; i < SIZE; i++){
        printf("%f\t",buffer[i]);
    }
    printf("\n");*/
    /*float * ptr; 
    for(int x=0; x < CHANNEL; x++){
        if(x==0)
            ptr = R;
        else if(x==1)
            ptr = G;
        else if(x==2)
            ptr = B;
        int counter = 0;
        for(int j = 0; j < HEIGHT; j++){
            for(int i = 0; i < WIDTH; i++){
                ptr[counter++] = buffer[i+j*WIDTH+x*WIDTH*HEIGHT];
            }
        }
    }*/

    /*RGB to YCbCr color space*/
    for(int j = 0; j < HEIGHT; j++){
        for(int i = 0; i < WIDTH; i++){
            Y_[i+j*WIDTH]=   buffer[i+j*WIDTH+0*WIDTH*HEIGHT] * 0.299 //R
                            +buffer[i+j*WIDTH+1*WIDTH*HEIGHT] * 0.587 //G
                            +buffer[i+j*WIDTH+2*WIDTH*HEIGHT] * 0.114;//B
            Cb[i+j*WIDTH]=   buffer[i+j*WIDTH+0*WIDTH*HEIGHT] *(-0.168736) //R
                            +buffer[i+j*WIDTH+1*WIDTH*HEIGHT] *(-0.331264) //G
                            +buffer[i+j*WIDTH+2*WIDTH*HEIGHT] * 0.5;       //B
            Cr[i+j*WIDTH]=   buffer[i+j*WIDTH+0*WIDTH*HEIGHT] * 0.5      //R
                            +buffer[i+j*WIDTH+1*WIDTH*HEIGHT] * 0.418688 //G
                            +buffer[i+j*WIDTH+2*WIDTH*HEIGHT] * 0.081312;//B
        }
    }

    return 0;
}