#include <stdio.h>
#include <stdlib.h>

float mul(float a, float b){
    return a*b;
}

float add(float a, float b){
    return a+b;
}

int main (){
    float (*fptr)(float,float);
    fptr = mul;
    printf("%f\n",fptr(3,5));
    fptr = add;
    printf("%f\n",fptr(3,5));
    return 0;
}