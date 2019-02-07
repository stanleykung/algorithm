#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define WIDTH 826
#define HEIGHT 540
#define CHANNEL 3
#define SIZE WIDTH*HEIGHT*CHANNEL
#define PI 3.14159265358979323846

float * create_dct_coefficients(float * array, int size){
    for(int n=0;n<8;n++){
		for(int m=0;m<8;m++){
			array[n*8+m] = cos((1./16.)*(2*m+1)*PI/2*n);
		}
	}
    return array;
}

int main(){
    //char filename[]=;
    FILE *fp;
    fp = fopen("/home/kungdehan/program_practice/github/algorithm/jpeg/jpeg_encoder/ncku.txt","r");
    if(fp == NULL){
        fputs ("File error",stderr); exit (1);
    }

    float * buffer = malloc(sizeof(float)*SIZE);
    /*float * R = malloc(sizeof(float)*WIDTH*HEIGHT);
    float * G = malloc(sizeof(float)*WIDTH*HEIGHT);
    float * B = malloc(sizeof(float)*WIDTH*HEIGHT);*/
    float * Y  = malloc(sizeof(float)*WIDTH*HEIGHT);
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

    /*extract RGB channel data*/
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
            // follow ITU-R BT.601 (formerly CCIR 601)
            Y[i+j*WIDTH] =   buffer[i+j*WIDTH+0*WIDTH*HEIGHT] * 0.299 //R
                            +buffer[i+j*WIDTH+1*WIDTH*HEIGHT] * 0.587 //G
                            +buffer[i+j*WIDTH+2*WIDTH*HEIGHT] * 0.114;//B
            Cb[i+j*WIDTH]=   buffer[i+j*WIDTH+0*WIDTH*HEIGHT] *(-0.168736) //R
                            +buffer[i+j*WIDTH+1*WIDTH*HEIGHT] *(-0.331264) //G
                            +buffer[i+j*WIDTH+2*WIDTH*HEIGHT] * 0.5;       //B
            Cr[i+j*WIDTH]=   buffer[i+j*WIDTH+0*WIDTH*HEIGHT] * 0.5      //R
                            +buffer[i+j*WIDTH+1*WIDTH*HEIGHT] * 0.418688 //G
                            +buffer[i+j*WIDTH+2*WIDTH*HEIGHT] * 0.081312;//B
            //printf("%f, %d,%d,%d\t", Y[i+j*WIDTH],(int)buffer[i+j*WIDTH+0*WIDTH*HEIGHT],(int)buffer[i+j*WIDTH+1*WIDTH*HEIGHT],(int)buffer[i+j*WIDTH+2*WIDTH*HEIGHT]);
        }
    }

    /*Chroma subsampling*/
    int sampling_mode=0;
    if(sampling_mode==0) // Full size
        printf("The sampling mode: 4:4:4\n");
    else if(sampling_mode==1){
        printf("The sampling mode: 4:2:2\n");
        /*NEED TO BE ADDED*/
    }
    else if(sampling_mode==2){
        printf("The sampling mode: 4:2:0\n");
        /*NEED TO BE ADDED*/
    }

    /*8x8 blocks splitting*/
    int block_num_x = (WIDTH%8==0)?  (WIDTH/8)  : ((WIDTH/8)+1);
    int block_num_y = (HEIGHT%8==0)? (HEIGHT/8) : ((HEIGHT/8)+1);
    float current_block_Y[64];
    float current_block_Cb[64];
    float current_block_Cr[64];
    long double current_dct_Y[64];
    long double current_dct_Cb[64];
    long double current_dct_Cr[64];
    long double zeros[64]={0};
    for(int y = 0; y < block_num_y; y++){
        for(int x = 0; x < block_num_x; x++){
            /*Within this part, the zeros padding and intensity shift will be also implemented.
            The zeros padding is for filling the image with zeros so that the image can be divied
            into 8*8 blocks. And, the intensity shift will shift the intensity range from [0,255]
            to [-128,127].*/
            //get the Y current block
            count = 0;
            memcpy(current_block_Y,zeros,sizeof(current_block_Y));
            for(int j=y*8+0; j <= (y+1)*8-1 && j < HEIGHT; j++){
                for(int i = x*8+0; i <= (x+1)*8-1 && i < WIDTH; i++){
                    current_block_Y[count++] = Y[i+j*8]-128;
                    //printf("%d, %f, %f\t", count, Y[i+j*8], current_block_Y[count-1]);
                }
            }
            //get the Cb current block
            count = 0;
            memcpy(current_block_Cb,zeros,sizeof(current_block_Cb));
            for(int j=y*8+0; j <= (y+1)*8-1 && j < HEIGHT; j++){
                for(int i = x*8+0; i <= (x+1)*8-1 && i < WIDTH; i++){
                    current_block_Cb[count++] = Cb[i+j*8]-128;
                }
            }
            //get the Cr current block
            count = 0;
            memcpy(current_block_Cr,zeros,sizeof(current_block_Cr));
            for(int j=y*8+0; j <= (y+1)*8-1 && j < HEIGHT; j++){
                for(int i = x*8+0; i <= (x+1)*8-1 && i < WIDTH; i++){
                    current_block_Cr[count++] = Cr[i+j*8]-128;
                }
            }

            /*Discrete Cosine Transform*/
            long double c_v, c_u, sum_Y, sum_Cb, sum_Cr;
            for(int v = 0; v < 8; v ++){
                c_v = (v==0)? 1./sqrt(2) : 1;
                for(int u = 0; u < 8; u++){
                    c_u = (u==0)? 1./sqrt(2) : 1;
                    sum_Y =0;
                    sum_Cb=0;
                    sum_Cr=0;
                    for(int j = 0; j < 8; j ++){
                        for(int i = 0; i < 8; i++){
                            sum_Y += current_block_Y[i+j*8] * cos((2*i+1)*u*PI / 16.) * cos((2*j+1)*v*PI / 16.);
                            sum_Cb+= current_block_Cb[i+j*8] * cos((2*i+1)*u*PI / 16.) * cos((2*j+1)*v*PI / 16.);
                            sum_Cr+= current_block_Cr[i+j*8] * cos((2*i+1)*u*PI / 16.) * cos((2*j+1)*v*PI / 16.);
                        }
                    }
                    current_dct_Y[v*8+u] = 0.25*c_u*c_v*sum_Y;
                    current_dct_Cb[v*8+u]= 0.25*c_u*c_v*sum_Cb;
                    current_dct_Cr[v*8+u]= 0.25*c_u*c_v*sum_Cr;
                }
            }

            /*printf("========\n%d, %d\n", x, y);
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    printf("%f\t", current_block_Y[j*8+i]);
                }
                printf("\n");
            }

            for(int v = 0; v < 8; v ++){
                for(int u = 0; u < 8; u++){
                    printf("%Lf\t", current_dct_Y[v*8+u]);
                }
                printf("\n\n");
            }*/

            /*Quantization*/
            // Luminance Quantization Table
            long double q_Y[64];
            long double q_Cb[64];
            long double q_Cr[64];
            double LDQT[64] = {16, 11, 10, 16, 24, 40, 51, 61,
                               12, 12, 14, 19, 26, 58, 60, 55,
                               14, 13, 16, 24, 40, 57, 69, 56,
                               14, 17, 22, 29, 51, 87, 80, 62,
                               18, 22, 37, 56, 68,109,103, 77,
                               24, 35, 55, 64, 81,104,113, 92,
                               49, 64, 78, 87,103,121,120,101,
                               72, 92, 95, 98,112,100,103, 99};
            //Chrominance Quantization Table
            double CDQT[64] = {17, 18, 24, 47, 99, 99, 99, 99,
                               18, 21, 26, 66, 99, 99, 99, 99,
                               24, 26, 56, 99, 99, 99, 99, 99,
                               47, 66, 99, 99, 99, 99, 99, 99,
                               99, 99, 99, 99, 99, 99, 99, 99,
                               99, 99, 99, 99, 99, 99, 99, 99,
                               99, 99, 99, 99, 99, 99, 99, 99,
                               99, 99, 99, 99, 99, 99, 99, 99,};
            for(int i=0; i< 64; i++){
                q_Y[i]  = round(current_dct_Y[i] / LDQT[i]);
                q_Cb[i] = round(current_dct_Cb[i]/ CDQT[i]);
                q_Cr[i] = round(current_dct_Cr[i]/ CDQT[i]);
                if(q_Y[i]==0) q_Y[i]=0; // remove minus zeros
                if(q_Cb[i]==0) q_Cb[i]=0;
                if(q_Cr[i]==0) q_Cr[i]=0;
            }
            printf("========\n%d, %d\n", x, y);
            for(int v = 0; v < 8; v ++){
                for(int u = 0; u < 8; u++){
                    printf("%Lf\t", q_Y[v*8+u]);
                }
                printf("\n\n");
            }

            /*Entropy coding*/
            //Zig-Zag Ordering Scaning
            int count1 = 0, count2 = 0, count3 = 3;
            int flag = 1;
            long double Z_Y[64];
            long double Z_Cb[64];
            long double Z_Cr[64];
            for(int i = 0; i < 8; i++){
                flag = flag*(-1); //change the direction
                for(int j = i; j >=0 ; j--){
                    Z_Y[count1++] = (flag > 0)? q_Y[j+(i-j)*8] : q_Y[j*8+(i-j)]; //7: dpwn
                    Z_Cb[count2++] = (flag > 0)? q_Cb[j+(i-j)*8] : q_Cb[j*8+(i-j)];
                    Z_Cr[count3++] = (flag > 0)? q_Cr[j+(i-j)*8] : q_Cr[j*8+(i-j)];
                }
            }
            //(0,7)->(1,7)->(2,6)
            for(int i = 8; i<=14; i++){
                flag = flag*(-1); //change the direction
                for(int j = i-7; j <= 7 ; j++){
                    Z_Y[count1++] = (flag > 0)? q_Y[j*8+(i-j)] : q_Y[j+(i-j)*8]; //8: up
                    Z_Cb[count2++] = (flag > 0)? q_Cb[j*8+(i-j)] : q_Cb[j+(i-j)*8];
                    Z_Cr[count3++] = (flag > 0)? q_Cr[j*8+(i-j)] : q_Cr[j+(i-j)*8];
                }
            }

            printf("========\n%d, %d\n", x, y);
            for(int v = 0; v < 8; v ++){
                for(int u = 0; u < 8; u++){
                    printf("%Lf\t", Z_Y[v*8+u]);
                }
                printf("\n\n");
            }

            // DPCM (Differential Pulse Code Modulation) for DC value
            /*Encode the difference from the DC component of previous 8×8 block*/

            // Run Length Encoding (RLE) for AC coefficients

            // Huffman coding
        }
    }
    return 0;
}