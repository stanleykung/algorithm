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
    CQ * q = &queue;
    queue.cur_size = SIZE;
    for(int i = 0; i < SIZE; i++)
        queue.data[i] = i;

    return q;
}

void PrintCQ(CQ * queue){
    //printf("%d\n", queue->cur_size);
    for(int i = 0; i < 10; i++){
        printf("%d\t", queue->cur_size);
        //printf("%d, %d\t", i, queue->data[i]);
    }
    printf("\n");
}

int main(){
    CQ * queue = InitializeCQ();
    PrintCQ(queue);
}