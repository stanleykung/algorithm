#include <stdio.h>
#include <stdlib.h>

typedef float (*Math)(float,float);

float mul(float a,float b){
    return a*b;
}

float add(float a, float b){
    return a+b;
}

float cal(float a, float b, Math op){
    return op(a,b);
}

int main(){
    printf("3 x 5 = %f\n", cal(3, 5, mul));
    Math op = add;
    printf("3 + 5 = %f\n", op(3,5));
    return 0;
}

/*http://hackgrass.blogspot.com/2017/07/cc-function-pointer-function-pointer.html*/