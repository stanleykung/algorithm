#include <stdio.h>
#include "MyStack.h"

#define MAX_SIZE 10

int main(){
	stack S;
	create_stack(&S);
	stack_print(&S);
	stack_push(&S,8);
	stack_print(&S);
	for(int i=1; i<10; i++)
		stack_push(&S,i);
	stack_print(&S);
	stack_push(&S,10);
	printf("Current Top:%d\n", stack_top(&S));
	for(int i=0; i<MAX_SIZE; i++){
		printf("%d\n", stack_pull(&S));
		stack_print(&S);
	}
	stack_pull(&S);
	return 0;
}
