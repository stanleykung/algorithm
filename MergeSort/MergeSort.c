#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

void print_arr_part(int * left, int * right){
	for(int *i = left; i <= right; i++)
		printf("%d\t", *i);
	printf("\n");
}

void merge(int * arr, int left, int center, int right){
	int templ = left;
	int tempr = center;

	int k = 0;
	int * temp = malloc(sizeof(int)*(right-left+1));

	if(templ<center && tempr<right+1){ // both sub-arrays are not finished
		if(arr[tempr]<arr[templ]){
			temp[k] = arr[tempr];
			tempr++;
			k++;
		}
		else{
			temp[k] = arr[templ];
			templ++;
			k++;
		}
	}
	else if(templ >= center){ // left sub-array is finished
		temp[k] = arr[tempr];
		tempr++;
		k++;
	}
	else{ // right sub-array is finished
		temp[k] = arr[templ];
		templ++;
		k++;
	}

	//put the sorted array back into the input array
	for(int i = 0; i<right-left+1; i++){
		arr[left+i] = temp[i];
	}

	/*if(templ<center && tempr<right+1){ // both sub-arrays are not finished
		if(arr[tempr]<arr[templ]){
			swap(&arr[tempr], &arr[templ]);
			print_arr(arr);
			printf("The index: %d, %d\n", templ, tempr);
			tempr++;
		}
		else
			templ++;
		}
	}
	else if(templ >= center){ // left sub-array is finished
		tempr++;
	}
	else if(tempr >= right+1){ // right sub-array is finished
		templ++;
	}
	else
		return;/*

	/*if(templ==center-1 && tempr ==right)
		if(arr[tempr]<arr[templ])
			swap(&arr[tempr], &arr[templ]);
		return;
	else if(templ==center-1){
		tempr++;
		if(arr[tempr]<arr[templ])
			swap(&arr[tempr], &arr[templ]);
	}*/
}

void sort(int * arr, int left, int right){
	int len = right-left;

	//if there is only one element in the array, just return the array (the end of divide)
	if(len == 0)
		return;// left == right
	else{
		//divided left sub-array
		printf("====> %d, %d, %d, %d\n", left, (left+right+1)/2-1, (left+right+1)/2, right);
		sort(arr, left, (left+right+1)/2-1);
		sort(arr, (left+right+1)/2,  right);
		printf("----> %d, %d, %d, %d\n", left, (left+right+1)/2-1, (left+right+1)/2, right);
		merge(arr, left, (left+right+1)/2, right);
	}
}

int main(){
	int arr[SIZE]={5,3,8,6,2,7,1,4};
	int len = (int)(sizeof(arr) / sizeof(int));
	print_arr(arr);
	printf("The length of array: %d\n", len);
	/*int count = 0;
	for(int i = 0; arr[i] != '\0'; i++){
		count++;
		printf("%d, %d\n", count, arr[i]);
	}
	printf("%d\n", count);*/
	//print_arr_part(&arr[1], &arr[length-2]);
	sort(arr, 0, len-1);
	print_arr(arr);
}
