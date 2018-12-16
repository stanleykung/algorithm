#include <stdio.h>

#define SIZE 10


struct CircularQueue{
    int cur_size;
    int front;
    int rear;
    int data[SIZE];
};

typedef struct CircularQueue CQ;

CQ * InitializeCQ(){
    CQ queue;
    queue.cur_size = SIZE;
    for(int i = 0; i < SIZE; i++)
        queue.data[i] = 0;
    return &queue;
}

void PrintCQ(CQ * queue){
    for(int i = 0; i < queue->cur_size; i++)
        printf("%d\t", queue->data[i]);
    printf("\n");
}

int main(){
    CQ * queue;
    queue = InitializeCQ();
    PrintCQ(queue);
}