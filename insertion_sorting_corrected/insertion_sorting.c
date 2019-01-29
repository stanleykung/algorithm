#include <stdio.h>
#include <stdlib.h>

void print_arr(int * arr,int SIZE){
	for(int i=0; i<SIZE; i++)
		printf("%d\t", *(arr+i));
	printf("\n");
}

void insert_sort(int * arr, int len){
    for(int i = 1; i < len; i++){
        int current = arr[i];
        int j = i-1;
        while(j>=0 && current < arr[j]){
            arr[j+1] = arr[j]; // push the element backward
            j--;
        }
        arr[j+1] = current;
        printf("The No. %d turn ", i);
        print_arr(arr,len);
    }
}

int main(){
    //int arr[]={4,3,2,10,12,1,5,6};
    int arr[]={5,2,4,6,1,3};
    int length = sizeof(arr) / sizeof(int);
    printf("The length of array: %d\n",length);
    print_arr(arr,length);

    insert_sort(arr,length);
    print_arr(arr,length);
}