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

void adjust(int * arr, int root, int n){ //n: the index of the last element in the heap (array implemented)
	int rootvalue = arr[root-1];
    int child = root * 2; // point to the left child of root
	
	while(child<=n){ //when the heap is not finished 
		if((child < n) && (arr[child-1] < arr[child+1-1]))
			child++; // point to the right child (owing to right child id larger)
		/*(child < n) make sure both left child and right child exit
		if child = n: means the current left child is the last element => there is no right child*/
		if(rootvalue >= arr[child-1]) break;
		else{
			arr[child/2-1] = arr[child-1]; // move the bigger child to parent
			child*=2; // moving down
		}
	}
	arr[child/2-1] = rootvalue;
}

void heapsort(int * arr, int n){
	
	/* make the unsorted array into the max heap*/
	//printf("Make the max heap\n");
	for(int i = n/2; i > 0; i--) // only sort the elements in the max heap with child
		adjust(arr, i , n);      // pass i = n/2...1 (real: n/2-1...0)

	/*find the max one by one*/
	//printf("find the max\n");
	for(int i = n; i > 1 ; i--){// i = n...2 (real: n-1...1)
		//printf("%d, %d\n", n, i);
		swap(&arr[1-1], &arr[i-1]); //arr[1-1] is the max current, and move to end.
		adjust(arr, 1, i-1);
	}
	//printf("detected the max\n");
}

int main(){
	int arr[SIZE]={5,3,8,6,2,7,1,4};
	print_arr(arr);
    //swap(&arr[0],&arr[1]);
	heapsort(arr,(int)(sizeof(arr) / sizeof(int)));
	print_arr(arr);
}