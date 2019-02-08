#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>    
    
int main(){
    int count = 0;
    int flag = 1;
    int q_Y[64];
    int Z_Y[64];
    for(int i = 0; i< 64; i++)
        q_Y[i]=i+1;

    /*for(int i = 0; i < 8; i++){
        flag = flag*(-1); //change the direction
        for(int j = i; j >=0 ; j--){
            Z_Y[count++] = (flag > 0)? q_Y[j+(i-j)*8] : q_Y[j*8+(i-j)]; //7: dpwn
        }
    }
    //(0,7)->(1,7)->(2,6)
    for(int i = 8; i<=14; i++){
        flag = flag*(-1); //change the direction
        for(int j = i-7; j <= 7 ; j++){
            Z_Y[count++] = (flag > 0)? q_Y[j*8+(i-j)] : q_Y[j+(i-j)*8]; //8: up
        }
    }*/
    for(int i = 0; i < 8; i++){
        flag = flag*(-1); //change the direction
        for(int j = i; j >=0 ; j--){
            printf("%d\n", count);
            Z_Y[count++] = (flag > 0)? q_Y[j+(i-j)*8] : q_Y[j*8+(i-j)]; //7: dpwn
                    //Z_Cb[count2++] = (flag > 0)? q_Cb[j+(i-j)*8] : q_Cb[j*8+(i-j)];
                    //Z_Cr[count3++] = (flag > 0)? q_Cr[j+(i-j)*8] : q_Cr[j*8+(i-j)];
        }
    }
            //(0,7)->(1,7)->(2,6)
    for(int i = 8; i<=14; i++){
        flag = flag*(-1); //change the direction
        for(int j = i-7; j <= 7 ; j++){
            printf("%d\n", count);
            Z_Y[count++] = (flag > 0)? q_Y[j*8+(i-j)] : q_Y[j+(i-j)*8]; //8: up
            
                    //Z_Cb[count2++] = (flag > 0)? q_Cb[j*8+(i-j)] : q_Cb[j+(i-j)*8];
                    //Z_Cr[count3++] = (flag > 0)? q_Cr[j*8+(i-j)] : q_Cr[j+(i-j)*8];
        }
    }
    printf("\n\n");


    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8 ; j++){
            printf("%d\t", q_Y[j+i*8]);
        }
        printf("\n");
    }
    printf("\n");
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8 ; j++){
            printf("%d\t", Z_Y[j+i*8]);
        }
        printf("\n");
    }

}
    