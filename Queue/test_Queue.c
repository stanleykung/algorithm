#include <stdio.h>
#include <stdlib.h>


struct MyQueue {
  int rear, front;
  int size;
  int capacity;
  float * data;
}

typedef struct MyQueue MyQueue;

MyQueue * CreateQueue(int capacity){
  MyQueue queue = MyQueue * malloc(sizeof(MyQueue));
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

void DeQueue(MyQueue * queue) {
  if(IsEmpty(queue))
    printf("%s\n", "The queue is empty which cannot pop any elements");
  else{
    float x;
    x = queue->data[(unsigned)queue->front];
    queue->data[(unsigned)queue->front] = 0;
    queue->front++;
    queue->size--;
  }
}
