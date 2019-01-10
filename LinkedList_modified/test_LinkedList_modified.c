#include <stdio.h>
#include <stdlib.h>

struct node
{
	float val;
	struct node * next;
};

typedef struct node node_t;

/*node_t * create_list(float x){
	node_t * head;
	head = (node_t *)malloc(sizeof(node_t));
	head->val=x;
	head->next=NULL;
	return head;
}*/

float get_element(node_t * n, unsigned x){
	node_t * current = n;
	for(int i=0; i<x; i++){
		current = current->next;
	}
	return current->val;
}

int get_length(node_t * n){
	int count=0;
	node_t * current = n;
	for(;;){
		if(current == NULL){
			count = 0;
			break;
		}
		else if(current->next==NULL){
			count++;
			break;
		}
		else if(current->next!=NULL){
			count++;
			current = current->next;
		}
	}
	/*while(current->next!=NULL){
		count++;
		current = current->next;
	}*/
	return count;
}

node_t * insert_bottom(node_t * n, float x){
	if(n==NULL){
		n = (node_t *)malloc(sizeof(node_t*));
		if(n==NULL) printf("The list fail to be created\n");
		n->val = x;
		n->next = NULL;
		return n;
	}
	else{
		// finding the bottom of the list
		node_t * current = n;
		while(current->next!=NULL){
			current = current->next;
		}
		//add the element at the bottom
		current->next = (node_t *)malloc(sizeof(node_t*));
		current->next->val=x;
		current->next->next=NULL;
		return n;
	}
	
}

node_t * insert_top(node_t * n, float x){
	//create new top node
	node_t * new_top;
	new_top = malloc(sizeof(node_t));
	new_top->val=x;
	new_top->next=n;//link the old list in the end of new top
	return new_top;
}

node_t * insert_order(node_t * n, float x, unsigned y){ // x: inserted number, y: inserted order
	node_t * current = n;
	node_t * parent = NULL;
	node_t * temp;
	temp = (node_t *)malloc(sizeof(node_t));
	temp->val = x;

	// finding the place to insert the element according to the input order
	if(y==0)
		return insert_top(n,x);
	//printf("%s\n", "This function insert_order cannot insert the element to the top, and you can use insert_top");
	else{
		for(int i=0; i<y; i++){
			parent = current;
			current = current->next; 
		}
		temp->next = current;
		parent->next = temp;
		return n;
	}
}

node_t * delete_bottom(node_t * n){
	node_t * current = n;
	node_t * parent = NULL;

	//if the list is empty, show the warning and jump out the function
	if(n==NULL){
		printf("%s\n", "The list is empty which cannot delete any element more!");
		return NULL;
	}
	else{
		//when there is only one element in the list
		//free the whole list
		if(current->next==NULL){
			free(current);
			return NULL;
		}

		//find the bottom of the list
		while(current->next!=NULL){
			parent = current;
			current = current->next;
		}
		parent->next = NULL;
		free(current);
		return n;
	}
}

node_t * delete_top(node_t * n){
	node_t * child = n->next;
	free(n);
	return child;
}

node_t * delete_order(node_t * n, int x){
	node_t * current = n;
	node_t * parent = NULL;

	//delete the element at the top
	if(x==0)
		return delete_top(n);

	//the input order is not in the range of size of list
	if(x >= get_length(n)){
		printf("%s\n", "The input order is out of range of the size of list");
		return n;
	}

	for(int i=0; i<x; i++){
		parent = current;
		current = current->next;
	}
	parent->next = current->next;
	free(current);
	return n;
}

void print_list(node_t * n){
	node_t * current = n;
	if(n==NULL)
		printf("%s\n", "The list is empty! Cannot print!");
	else{
		while(current!=NULL){
			printf("%f\t", current->val);
			current=current->next;
		}
		printf("\n");
	}
}

int main(){
	node_t * head = NULL;
	head = insert_bottom(head,10);
	head = insert_bottom(head,20);
	print_list(head);
	head = insert_bottom(head,30);
	head = insert_top(head,40);
	print_list(head);
	head = insert_order(head,50,1);
	print_list(head);
	head = insert_order(head,60,0);
	print_list(head);
	printf("%f\n",get_element(head,2));
	printf("length: %d\n",get_length(head));
	
	printf("%s\n", "-----------------");
	head = delete_bottom(head);
	print_list(head);

	printf("%s\n", "-----------------");
	for(int i=0;i<5;i++){
		printf("---\n");
		if(head!=NULL){
			printf("delete the element in the bottom\n");
			head = delete_bottom(head);
			print_list(head);
		}
		else{
			printf("%s\n", "The list is empty which cannot delete any element more!");
		}
		printf("current length: %d\n",get_length(head));
	}

	printf("%s\n", "-----------------");
	head = insert_bottom(head,10);
	print_list(head);
	for(int i=20; i<70; i=i+10)
		head = insert_bottom(head,i);
	print_list(head);
	head = delete_top(head);
	print_list(head);
	head = delete_order(head,2);
	print_list(head);
	head = delete_order(head,0);
	print_list(head);
	head = delete_order(head,2);
	print_list(head);
	head = delete_order(head,2);
	print_list(head);
}
