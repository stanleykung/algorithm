#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int cal_size(long double val){
    long double abs_ = fabsl(val);
    int s = 1;
    int count = 1;
    //printf("%Lf\n",abs_);
    /*while(abs_ > s){ // 2^1-1...2^0,2^2-1...2^1,2^3-1...2^2,2^4-1...2^3 
        s*=2;
        count++;
    }*/
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

int main(){
    int x = cal_size(-1023);
    printf("%d\n",x);
    return 0;
}