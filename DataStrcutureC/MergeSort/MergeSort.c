#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 8

void print_arr(int * arr){
	for(int i=0; i<SIZE; i++)
		printf("%d\t", *(arr+i));
	printf("\n");
}

void merge(int * init, int * merged, int i, int m, int n){
	int x = i;
	int y = m+1;
	int k = i;
	//printf("Start to merge from %d, from %d to %d\n", i, m , n);
	while(x <= m && y <= n){ // both arrays segments (s and s) are not finished.
		if(init[x]<=init[y])
			merged[k++] = init[x++];
		else
			merged[k++] = init[y++];
	}
	if(x <= m){
		// first segment array is not finished, and the second segment is finished
		for(int t=x; t<= m; t++)
			merged[k++] = init[t];
	}
	else{
		// second segment array is not finished, and the first segment is finished
		for(int t=y; t<= n; t++)
			merged[k++] = init[t];
	}
}

/*pass 2*s array to "merge function" to merge*/
void mergepass(int * init, int * merged, int n, int s){
	int i;
	//printf("%s\n", "Enter mergepass");
	for(i=0; i<=n-2*s; i+=2*s){ // separate the init array (unsorted) into multiple 2*s segment
		merge(init, merged, i, i+s-1, i+2*s-1); // merge (i~i+s-1,i+s~i+2*s-1)
	}
	//print_arr(merged);
	if(i+s < n) //if the reminded array segment is large than s
		merge(init, merged, i, i+s-1, n-1); // merge (i~i+s-1,i+s~n-1)
	else{
		for(int x=i; x<=n-1; x++)
			merged[x] = init[x];
	}
}

void mergesort(int * arr, int n){ // n is the lenth of the array
	int s = 1;
	int extra[SIZE];
	while(s<n){
		mergepass(arr,extra,n,s); // pass the merged array from a(unsorted) to extra
		s*=2;
		mergepass(extra,arr,n,s); // pass the merged array from extra(unsorted) to a
		s*=2;
	}
}

int main(){
	int arr[SIZE]={5,3,8,6,2,7,1,4};
	print_arr(arr);
	mergesort(arr,(int)(sizeof(arr) / sizeof(int)));
	print_arr(arr);
}
