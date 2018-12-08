#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 8

void print_arr(int * arr){
	for(int i=0; i<SIZE; i++)
		printf("%d\t", *(arr+i));
	printf("\n");
}

void swap(int * a, int * b){
    int x;
    x  = *a;
    *a = *b;
    *b = x;
}

void adjust(int * arr, int root, int n){ // the index of the last element in the heap (array implemented)
    int child = root * 2; // point to the left child of root
	while(child<=n){
		if((child < n) && (arr[child] < arr[child+1]))
			child++; // point to the right child (owing to right child id larger)
		/*(child < n) make sure both left child and right child exit
		if child = n: means the current left child is the last element => there is no right child*/
		if(arr[root] >= arr[child]) break;
		else{
			
		}
	}
}

int main(){
	int arr[SIZE]={5,3,8,6,2,7,1,4};
	print_arr(arr);
    //swap(&arr[0],&arr[1]);
	//heapsort(arr,(int)(sizeof(arr) / sizeof(int)));
	print_arr(arr);
}