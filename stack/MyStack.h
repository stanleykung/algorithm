#ifndef MYSTACK_H_   /* Include guard */
#define MYSTACK_H_

#define MAX_SIZE 10

struct  stack
{
	int cur_size;
	int data[MAX_SIZE];
};

typedef struct stack stack;

void create_stack(stack *s);

int Is_Full(stack *s);

int Is_Empty(stack *s);

int stack_top(stack *s);

void stack_push(stack *s, int x);

int stack_pull(stack *s);

void stack_print(stack *s);

#endif
