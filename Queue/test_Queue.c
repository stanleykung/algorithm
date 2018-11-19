#include <stdio.h>
#include <stdlib.h>


struct MyQueue {
  int rear, front;
  int size;
  int capacity;
  float * data;
};

typedef struct MyQueue MyQueue;

MyQueue * CreateQueue(int capacity){
  MyQueue * queue = (MyQueue *)malloc(sizeof(MyQueue));
  queue->rear = 0;
  queue->front = 0;
  queue->size = 0;
  queue->capacity = capacity;
  queue->data = (float *)malloc(sizeof(float)*capacity);
  return queue;
}

void EnQueue(MyQueue * queue, float x){
  if(IsFull(queue))
    printf("%s\n", "The queue is full which cannot input more data!");
  else{
    queue->data[(unsigned)queue->rear] = x;
    queue->rear++;
    queue->size++;
  }
}

float DeQueue(MyQueue * queue) {
  if(IsEmpty(queue))
    printf("%s\n", "The queue is empty which cannot pop any elements");
  else{
    float x;
    x = queue->data[(unsigned)queue->front];
    queue->data[(unsigned)queue->front] = 0;
    queue->front++;
    queue->size--;
    return x;
  }
}

int IsFull(MyQueue * queue){
  return (queue->size==queue->capacity);
}

int IsEmpty(MyQueue * queue){
  return (queue->front==queue->rear);
}

void PrintQueue(MyQueue * queue){
  for(int i=queue->front;i<queue->rear;i++)
    printf("%f\t", queue->data[(unsigned)i]);
  printf("\n");
}

int main(){
  MyQueue * queue;
  queue = CreateQueue(3);
  EnQueue(queue,1);
  EnQueue(queue,2);
  EnQueue(queue,3);
  PrintQueue(queue);
  EnQueue(queue,4);
  printf("Pop the element: %f\n", DeQueue(queue));
  PrintQueue(queue);
  for (size_t i = 0; i < 3; i++) {
    printf("Pop the element: %f\n", DeQueue(queue));
  }
}
