
#include <stdio.h>
#include <stdlib.h>

typedef int (*CMP)(int, int);
//void swap(int &, int &);
//bool larger(int a, int b);
//bool smaller(int a, int b);
//void sort(int *arr, int length, CMP);

void swap(int *a, int *b){
    int t = *a; 
    *a = *b; 
    *b = t;
}
int larger(int a, int b){
    return a>b;
}
int smaller(int a, int b){
    return a>b;
}
void sort(int *arr, int length, CMP compare){
    for(int i=1; i < length; i++){
        for(int j=0; j < i; j++) { 
            if(compare(arr[j+1], arr[j] > 0)) { 
                swap(&arr[j+1], &arr[j]); 
            } 
        } 
    } 
}

void print_arr(int * arr, int len){
    for(int i = 0; i < len; i++)
        printf("%d\t",arr[i]);
    printf("\n");
}

int main() { 
    int arr[] = {2, 7, 9, 1};
    int length = sizeof(arr)/sizeof(int);
    print_arr(arr,length);
    sort(arr, 4, larger);  //排序後arr為{9,7,2,1}
    print_arr(arr,length);
    sort(arr, 4, smaller); //排序後arr為{1,2,7,9}
    print_arr(arr,length);
    return 0; 
} 

