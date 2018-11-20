#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 9

int main(){
	
	//create the array that need to be aorted
	//int * arr;
	//arr = malloc(sizeof(int)*SIZE);
	int arr[SIZE] = {1, 12, 5, 26, 7, 14, 3, 7, 2};
	for(int i=0; i<SIZE; i++)
		//printf("%d\n", arr[i]);
		printf("%d\t", *(arr+i));
	printf("\n");

	//Pick up the pivot randomly
	srand( time(NULL) );
	unsigned pindex = (unsigned)rand() % SIZE;
	int pivot = arr[pindex];
	printf("Index: %d, pivot: %d\n", pindex, pivot);

	return 0;
}

//http://www.algolist.net/Algorithms/Sorting/Quicksort