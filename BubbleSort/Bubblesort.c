#include <stdio.h>
#include <stdlib.h>

//#define SIZE 9
#define SIZE 8

void swap(int * arr, int x, int y){
	int temp;
	temp = arr[x];
	arr[x] = arr[y];
	arr[y] = temp;
}

void swap2(int * a, int * b){
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

int compare(int a, int b){
	return (a>=b); // larger and equal to: 1, smaller: 0
}

int main(){
	//int arr[SIZE] = {1, 12, 5, 26, 7, 14, 3, 7, 2};
	int arr[SIZE]={4,3,2,10,12,1,5,6};

	printf("%s\n", "------");
	for(int i=0; i<SIZE; i++)
		//printf("%d\n", arr[i]);
		printf("%d\t", *(arr+i));
	printf("\n");

	printf("%s\n", "------");
	swap(arr, 1, 2);
	print_arr(arr);
	swap2(&arr[1], &arr[2]);
	print_arr(arr);

	printf("%s\n", "---Start Sorting---");
	for(int i = SIZE-1; i>=0; i--){
		for(int j = 0; j<i; j++){
			if(arr[j]>arr[j+1])
				swap2(&arr[j], &arr[j+1]);
		}
	}
	printf("%s\n", "After sorting:");
	print_arr(arr);
}