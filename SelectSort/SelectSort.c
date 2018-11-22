#include <stdio.h>
#include <stdlib.h>

#define SIZE 8


void swap(int * a, int * b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void print_arr(int * arr){
	for(int i=0; i<SIZE; i++)
		printf("%d\t", *(arr+i));
	printf("\n");
}

int main(){
	int arr[SIZE]={5,3,8,6,2,7,1,4};
	print_arr(arr);

	for(int i=0; i<SIZE; i++){
		for(int j=i+1; j<SIZE; j++){
			if(arr[j] < arr[i])
				swap(&arr[i], &arr[j]);
		}
	}
	print_arr(arr);
}