#include <stdio.h>
#include <stdlib.h>

#define SIZE 6


struct CircularQueue{
    int cur_size;
    int front; // point to previous element of the first element in the queue
    int rear; // point to the last element in the queue
    char data[SIZE];
};

typedef struct CircularQueue CQ;

CQ * InitializeCQ(){
    CQ * queue;
    queue = (CQ *)malloc(sizeof(CQ));
    // initialize the size, pointer and data inside
    queue->cur_size = SIZE;
    queue->front = 0; 
    queue->rear = 0;
    for(int i = 0; i < queue->cur_size; i++)
        queue->data[i] = '0';
    return queue;
}

int IsEmpty(CQ * queue){
    return (queue->front==queue->rear);
}

int IsFull(CQ * queue){
    return (queue->front==(queue->rear+1) % queue->cur_size);
}

void push(CQ * queue, int x){
    if(IsFull(queue))
        printf("The queue is full, cannot add any element anymore.\n");
    else{
        queue->rear=(queue->rear+1) % queue->cur_size;
        queue->data[queue->rear] = x;
    }
}

char pull(CQ * queue){
    if(IsEmpty(queue))
        printf("The queue is empty, cannot pull any element anymore.\n");
    else{
        queue->front=(queue->front+1) % queue->cur_size;
        char temp = queue->data[queue->front];
        queue->data[queue->front] = 0;
        return temp;
    }
}

void PrintCQ(CQ * queue){
    for(int i = 0; i < queue->cur_size; i++){
        printf("%c\t", queue->data[i]);
    }
    printf(";");
    printf("%d, %d\n", queue->front, queue->rear);
}

int search(CQ * queue, char c){
    for(int i = queue->front+1; i != (queue->rear+1) % queue->cur_size; i=(i+1) % queue->cur_size){
        if(queue->data[i] == c){
            return i;
        }
    }
    return -1;
}

int main(){
    int x;
    char string[] = {'h', 'e', 'l', 'l', 'o'};
    char *s = string;
    int length = sizeof(string) / sizeof(string[0]);

    for(int i = 0; i < length; i ++)
        printf("%c\t", s[i]); // same to "printf("%c\t", string[i]);"
    printf("\n");

    CQ * queue = InitializeCQ();
    PrintCQ(queue);

    for(int i = 0; i < length; i ++)
        push(queue,s[i]);
    PrintCQ(queue);

    if((x = search(queue,'c')) >= 0)
        printf("Hits with c char in the %d index\n", x);
    else
        printf("No Hit with c\n");

    if((x = search(queue,'l')) >= 0)
        printf("Hits with l char in the %d index\n", x);
    else
        printf("No Hit with l\n");

    return 0;
}