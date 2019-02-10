#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define WIDTH 826
#define HEIGHT 540
#define CHANNEL 3
#define SIZE WIDTH*HEIGHT*CHANNEL
#define PI 3.14159265358979323846

// Luminance Quantization Table
double LDQT[64] = { 16, 11, 10, 16, 24, 40, 51, 61,
                    12, 12, 14, 19, 26, 58, 60, 55,
                    14, 13, 16, 24, 40, 57, 69, 56,
                    14, 17, 22, 29, 51, 87, 80, 62,
                    18, 22, 37, 56, 68,109,103, 77,
                    24, 35, 55, 64, 81,104,113, 92,
                    49, 64, 78, 87,103,121,120,101,
                    72, 92, 95, 98,112,100,103, 99};
// Chrominance Quantization Table
double CDQT[64] = { 17, 18, 24, 47, 99, 99, 99, 99,
                    18, 21, 26, 66, 99, 99, 99, 99,
                    24, 26, 56, 99, 99, 99, 99, 99,
                    47, 66, 99, 99, 99, 99, 99, 99,
                    99, 99, 99, 99, 99, 99, 99, 99,
                    99, 99, 99, 99, 99, 99, 99, 99,
                    99, 99, 99, 99, 99, 99, 99, 99,
                    99, 99, 99, 99, 99, 99, 99, 99,};

// Typical Huffman tables
// Luminance DC coefficient differences
char * luminance_DC_Huff[12]={"00","010","011","100","101","110","1110","11110","111110","1111110","11111110","111111110"};
// Chrominance DC coefficient differences
char * chrominance_DC_Huff[12]={"00","01","10","110","1110","11110","111110","1111110","11111110","111111110","1111111110","11111111110"};
// Luminance AC coefficients
char * luminance_AC_Huff[162]={
    "00","01","100","1011","11010","1111000","11111000","1111110110","1111111110000010","1111111110000011",
    "1100","11011","1111001","111110110","11111110110","1111111110000100","1111111110000101","1111111110000110","1111111110000111","1111111110001000",
    "11100","11111001","1111110111","111111110100","1111111110001001","1111111110001010","1111111110001011","1111111110001100","1111111110001101","1111111110001110",
    "111010","111110111","111111110101","1111111110001111","1111111110010000","1111111110010001","1111111110010010","1111111110010011","1111111110010100","1111111110010101",
    "111011","1111111000","1111111110010110","1111111110010111","1111111110011000","1111111110011001","1111111110011010","1111111110011011","1111111110011100","1111111110011101",
    "1111010","11111110111","1111111110011110","1111111110011111","1111111110100000","1111111110100001","1111111110100010","1111111110100011","1111111110100100","1111111110100101",
    "1111011","111111110110","1111111110100110","1111111110100111","1111111110101000","1111111110101001","1111111110101010","1111111110101011","1111111110101100","1111111110101101",
    "11111010","111111110111","1111111110101110","1111111110101111","1111111110110000","1111111110110001","1111111110110010","1111111110110011","1111111110110100","1111111110110101",
    "111111000","111111111000000","1111111110110110","1111111110110111","1111111110111000","1111111110111001","1111111110111010","1111111110111011","1111111110111100","1111111110111101",
    "111111001","1111111110111110","1111111110111111","1111111111000000","1111111111000001","1111111111000010","1111111111000011","1111111111000100","1111111111000101","1111111111000110",
    "111111010","1111111111000111","1111111111001000","1111111111001001","1111111111001010","1111111111001011","1111111111001100","1111111111001101","1111111111001110","1111111111001111",
    "1111111001","1111111111010000","1111111111010001","1111111111010010","1111111111010011","1111111111010100","1111111111010101","1111111111010110","1111111111010111","1111111111011000",
    "1111111010","1111111111011001","1111111111011010","1111111111011011","1111111111011100","1111111111011101","1111111111011110","1111111111011111","1111111111100000","1111111111100001",
    "11111111000","1111111111100010","1111111111100011","1111111111100100","1111111111100101","1111111111100110","1111111111100111","1111111111101000","1111111111101001","1111111111101010",
    "1111111111101011","1111111111101100","1111111111101101","1111111111101110","1111111111101111","1111111111110000","1111111111110001","1111111111110010","1111111111110011","1111111111110100",
    "1111111111110101","1111111111110110","1111111111110111","1111111111111000","1111111111111001","1111111111111010","1111111111111011","1111111111111100","1111111111111101","1111111111111110"
};

struct STACK
{
    int data[10];
    int top;
};
typedef struct STACK stack;

void push(stack * s, int val){
    s->data[s->top++] = val;
}

int pop(stack * s){
    int temp = s->data[s->top-1];
    s->top = s->top -1;
    return temp;
}

struct linked_list{
    int runlength;
    int size;
    int amplitude;
    struct linked_list * next;
};
typedef struct linked_list RLE;

RLE * add_bottom(RLE * list, int run, int s, int am){
    if(list==NULL){
        list = malloc(sizeof(RLE));
        list->runlength = run;
        list->size = s;
        list->amplitude = am;
        list->next = NULL;
    }
    else{
        RLE * current = list;
        while(current->next){
            current=current->next;
        }
        current->next = malloc(sizeof(RLE));
        current->next->runlength = run;
        current->next->size = s;
        current->next->amplitude = am;
        current->next->next = NULL;
    }
    return list;    
}

void delete_list(RLE * list){
    RLE * temp;
    RLE * current = list;
    while(current->next){
        temp = current;
        current = current->next;
        free(temp);
    }
}

void print_list(RLE * list){
    RLE * current = list;
    while(current){
        printf("(%d,%d),%d ", current->runlength, current->size, current->amplitude);
        current = current->next;
    }
}

int cal_size(long double val){
    long double abs_ = fabsl(val);
    int s = 1;
    int count = 1;
    if(val == 0) // for DC difference
        return 0;
    while(1){
        if(s*2-1 >= abs_ && s <= abs_){
            return count;
        }
        else{
            s*=2;
            count++;
        }
    }
}

int RLE_codeword(RLE* list, int * array, int length){
    int num = 0; // number of codeword in array
    int cur_index;
    RLE * current = list;
    char * temp;
    while(current){
        // get the index of huffman table for codeword
        if(current->runlength == 0 && current->size ==0)
            temp = "1010";
        else if(current->runlength == 15 && current->size ==0)
            temp = "11111111001";
        else{
            cur_index = current->runlength*10 + current->size;
            temp = luminance_AC_Huff[cur_index-1];
        }
        // store the codeword into array
        int code;
        // symbol-1
        for(int i = 0; i < strlen(temp); i++){
            code = (int)(temp[i] - '0');
            array[num++] = code;
            if(num>=length)
                printf("The space is not enough\n");
        }
        //symbol-2, conversion from the decimal to binary
        int x = current->amplitude;
        stack s;
        s.top=0;
        while(x > 0){    
            push(&s,x % 2);
            x = x /2;
        }
        int end = s.top;
        for(int i = 0; i < end; i++)
            array[num++] = pop(&s);

        // move to next node in RLE
        current = current->next;
    }
    return num;
}

int DC_codeword(long double * iarray, int y, int x, int * oarray, int length){ // conversion the DC difference to codeword by lookup the huffman table
    int num = 0, size, amplitude, code;
    char * temp;
    long double current_value;
    for(int i = 0; i < y; i++){
        for(int j = 0; j < x; j++){
            current_value = iarray[i*x+j];
            size = cal_size(current_value);
            amplitude = (current_value < 0)? current_value - (-1)*pow(2,size) -1 : pow(2,size-1) + (current_value - pow(2,size-1));
            // get the codeword for symbol-1 by looking up the table
            if(size>=0 && size<=11){
                temp = luminance_DC_Huff[size];
                for(int m = 0; m < strlen(temp); m++){
                    code = (int)(temp[m] - '0');
                    oarray[num++] = code;
                    if(num>=length)
                        printf("The space is not enough\n");
                }
            }
            else{
                printf("The size of DC difference is over the standard range\n");
            }
            // add the codeword of symbol-2
            int x = amplitude;
            stack s;
            s.top=0;
            while(x > 0){    
                push(&s,x % 2);
                x = x /2;
            }
            int end = s.top;
            for(int m = 0; m < end; m++){
                oarray[num++] = pop(&s);
                if(num>=length)
                    printf("The space is not enough\n");
            }       
        }
    }
    return num;
}

int main(){
    //char filename[]=;
    FILE *fp;
    fp = fopen("ncku.txt","r");
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

    /*JPEG mode*/
    printf("This is Baseline Sequential mode\n");

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
    long double * all_DC_Y;
    long double * all_DC_Cb;
    long double * all_DC_Cr;
    long double * all_difference_DC_Y;
    long double * all_difference_DC_Cb;
    long double * all_difference_DC_Cr;
    all_DC_Y  = calloc(block_num_y * block_num_x, sizeof(long double)); //initialize with zeros
    all_DC_Cb = calloc(block_num_y * block_num_x, sizeof(long double));
    all_DC_Cr = calloc(block_num_y * block_num_x, sizeof(long double));
    all_difference_DC_Y  = calloc(block_num_y * block_num_x, sizeof(long double)); //initialize with zeros
    all_difference_DC_Cb = calloc(block_num_y * block_num_x, sizeof(long double));
    all_difference_DC_Cr = calloc(block_num_y * block_num_x, sizeof(long double));
    int runlength, size, amplitude, end_of_block, num_code;
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
            long double q_Y[64];
            long double q_Cb[64];
            long double q_Cr[64];
            for(int i=0; i< 64; i++){
                q_Y[i]  = round(current_dct_Y[i] / LDQT[i]);
                q_Cb[i] = round(current_dct_Cb[i]/ CDQT[i]);
                q_Cr[i] = round(current_dct_Cr[i]/ CDQT[i]);
                if(q_Y[i]==0) q_Y[i]=0; // remove minus zeros
                if(q_Cb[i]==0) q_Cb[i]=0;
                if(q_Cr[i]==0) q_Cr[i]=0;
            }
            /*printf("========\n%d, %d\n", x, y);
            for(int v = 0; v < 8; v ++){
                for(int u = 0; u < 8; u++){
                    printf("%Lf\t", q_Y[v*8+u]);
                }
                printf("\n\n");
            }*/

            /*Entropy coding*/
            //Zig-Zag Ordering Scaning
            int count1 = 0, count2 = 0, count3 = 0;
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

            /*printf("========\n%d, %d\n", x, y);
            for(int v = 0; v < 8; v ++){
                for(int u = 0; u < 8; u++){
                    printf("%Lf\t", Z_Y[v*8+u]);
                }
                printf("\n\n");
            }*/

            /* DPCM (Differential Pulse Code Modulation) for DC value*/
            //Encode the difference from the DC component of previous 8×8 block
            //printf("%d, %d\n", y, x);
            all_DC_Y[y*block_num_x+x]  = Z_Y[0]; //- all_difference_DC_Y[y*block_num_x+x-1];
            all_DC_Cb[y*block_num_x+x] = Z_Cb[0];//- all_difference_DC_Cb[y*block_num_x+x-1];
            all_DC_Cr[y*block_num_x+x] = Z_Cr[0];//- all_difference_DC_Cr[y*block_num_x+x-1];
            //printf("%Lf\t",Z_Y[0]);

            /*Run Length (Level) Encoding (RLE) for AC coefficients*/
            /*conversion of the quantized DCT coefficients into an intermediate sequence of symbols
              and assignment of variable-length codes to the symbols.*/
            /* Intermediate entropy coding representations: 
                ---SYMBOL1---
                1). runlength (4 bits): consecutive number of "zeros" AC, 
                2). size (4bits): number of bits to encode AMPLITUDE
                ---SYMBOL2---
                3). amplitude: the non-zero AC 
               (15,0) is 16 zeros at most 3 times. (48 zeros)
               ( 0,0) is the end of block. */
            runlength = 0;
            size = 0;
            amplitude = 0;
            end_of_block = 63;
            RLE * list = NULL;
            // find the end of block (find the first non-zero coefficients from end to beginning.)
            for(int i = 63; i >=1; i--){
                if(Z_Y[i]==0){
                    if(i==1){
                        end_of_block=1;
                    }
                    continue;
                }
                else
                {
                    end_of_block = i;
                    break;
                }
            }
            // calculate the symbol-1 and symbol-2 and add into the linked list
            for(int i = 1; i <= end_of_block; i++) { // Only AD coefficients
                if(Z_Y[i]==0){
                    if(runlength==15){ // add the current zero, there 16 zeros => send (15,0)
                        list = add_bottom(list, 15, 0, 0);
                        runlength = 0;
                    }
                    else
                        runlength++;
                }
                else{
                    size = cal_size(Z_Y[i]);
                    amplitude = (Z_Y[i] < 0)? Z_Y[i] - (-1)*pow(2,size) -1 : pow(2,size-1) + (Z_Y[i] - pow(2,size-1));
                    list = add_bottom(list,runlength,size,amplitude);
                    runlength = 0;
                }
            }
            list = add_bottom(list, 0,0,0);
            printf("\n========\nRLE\n");
            print_list(list);
            printf("\n");

            // Huffman coding
            /*symbol1(run+size->catergory)->categroy(based on table p.149)->Huffman Codeword*/
            /*symbol1 is encoded with variable-length code (VLC) from Huffman table (at most 16 bits)
              symbol2 is encoded with variable-length integer (VLI) code = Amplitude (index code,the position in cater) (at most 10 bits) */
            int codeword[1700]={0}; // 63*(16+10) = 1638
            num_code = RLE_codeword(list,codeword,1700);
            printf("========\nCodeword\n");
            for(int i = 0; i< num_code; i++){
                printf("%d ", codeword[i]);
            }

            delete_list(list);
        }
    }
    
    
    /*Coding of DC Coefficients*/
    printf("\n\nDC Difference:\n");
    printf("Use the default Huffman table\n");
    for(int i = 0; i < block_num_y; i++){
        for(int j = 0; j < block_num_x; j++){
            if(i==0 && j==0){
                all_difference_DC_Y[i*block_num_x+j] = all_DC_Y[i*block_num_x+j];
                all_difference_DC_Cb[i*block_num_x+j] = all_DC_Cb[i*block_num_x+j];
                all_difference_DC_Cr[i*block_num_x+j] = all_DC_Cr[i*block_num_x+j];
            }
            else{
                all_difference_DC_Y[i*block_num_x+j] = all_DC_Y[i*block_num_x+j]-all_DC_Y[i*block_num_x+j-1];
                all_difference_DC_Cb[i*block_num_x+j] = all_DC_Cb[i*block_num_x+j]-all_DC_Cb[i*block_num_x+j-1];
                all_difference_DC_Cr[i*block_num_x+j] = all_DC_Cr[i*block_num_x+j]-all_DC_Cr[i*block_num_x+j-1];
            }
            printf("%d\t", (int)all_difference_DC_Y[i*block_num_x+j]);
            if((i*block_num_x+j+1) % 16 ==0)
                printf("\n");
        }
        //printf("\n");
    }

    // coversion DC difference to codeword (Lookup the Huffman table)
    /*difference->SIZE=>categroy(based on table p.149)->
      Huffman Code(category,VLC,symbol1)+index code(the position in cater,VLI,symbol2)*/
    /*long double current_value;     
    for(int i = 0; i < block_num_y; i++){
        for(int j = 0; j < block_num_x; j++){
            //all_difference_DC_Y[i*block_num_x+j]
            current_value = all_difference_DC_Y[i*block_num_x+j];
            size = cal_size(current_value);
            amplitude = (current_value < 0)? current_value - (-1)*pow(2,size) -1 : pow(2,size-1) + (current_value - pow(2,size-1));
            num_code = DC_codeword(codeword,size,amplitude);
        }
    }*/
    int * codeword; // block_num_y*block_num_x*(9+10)
    int code_size = block_num_y * block_num_x*19;
    codeword = calloc(code_size, sizeof(int));
    num_code = DC_codeword(all_difference_DC_Y,block_num_y, block_num_x,codeword,code_size);
    printf("========\nCodeword\n");
    for(int i = 0; i< num_code; i++){
        printf("%d ", codeword[i]);
    }

    free(buffer);
    free(Y);
    free(Cb);
    free(Cr);
    free(all_difference_DC_Y);
    free(all_difference_DC_Cb);
    free(all_difference_DC_Cr);
    return 0;
}