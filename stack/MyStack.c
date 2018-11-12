#include <stdio.h>
#include "MyStack.h"

/*#define MAX_SIZE 10


struct  stack
{
	int cur_size;
	int data[MAX_SIZE];
};
typedef struct stack stack;*/

void create_stack(stack *s){
	s->cur_size = 0;
	for(int i=0; i<MAX_SIZE; i++)
		s->data[i]=0;
}

int Is_Full(stack *s){
	if(s->cur_size>=MAX_SIZE)
		//printf("%s\n", "The stack is full");
		return 1;
	else
		return 0;
}

int Is_Empty(stack *s){
	if(s->cur_size==0)
		return 1;
	else
		return 0;
}

int stack_top(stack *s){
	if(Is_Empty(s)){
		printf("%s\n", "The stack is empty!!\n");
		return -1;
	}
	else
		return s->data[s->cur_size-1];
}

void stack_push(stack *s, int x){
	if(Is_Full(s))
		printf("%s\n", "The stack is full, which cannot push any elements anymore!!\n");
	else{
		s->data[s->cur_size]=x;
		s->cur_size++;
	}
}

int stack_pull(stack *s){
	int top;
	if(Is_Empty(s))
		printf("%s\n", "The stack is empty!!\n");
	else{
		top = s->data[s->cur_size-1];
		s->data[s->cur_size-1]=0;
		s->cur_size--;
		return top;
	}

}

void stack_print(stack *s){
	for(int i=0; i<MAX_SIZE; i++)
		printf("%d\t", s->data[i]);
	printf("\n");
}

