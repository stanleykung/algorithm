#include <stdio.h>
#include <stdlib.h>

#define SIZE 10


struct CircularQueue{
    int cur_size;
    int front; // point to previous element of the first element in the queue
    int rear; // point to the last element in the queue
    int data[SIZE];
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
        queue->data[i] = 0;
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

int pull(CQ * queue){
    if(IsEmpty(queue))
        printf("The queue is empty, cannot pull any element anymore.\n");
    else{
        queue->front=(queue->front+1) % queue->cur_size;
        int temp = queue->data[queue->front];
        queue->data[queue->front] = 0;
        return temp;
    }
}

void PrintCQ(CQ * queue){
    for(int i = 0; i < queue->cur_size; i++){
        printf("%d\t", queue->data[i]);
    }
    printf(";");
    printf("%d, %d\n", queue->front, queue->rear);
}

int main(){
    int x;
    CQ * queue = InitializeCQ();
    PrintCQ(queue);

    //
    for(int i = 10; i < 60; i=i+10)
        push(queue, i);
    PrintCQ(queue);

    //
    for(int i = 0; i < 6; i++)
        x = pull(queue);
    PrintCQ(queue);

    //
    for(int i = 0; i < 10; i++)
        push(queue,(i+1)*10);
    PrintCQ(queue);
}