#ifndef QUEUE
#define QUEUE

#include "basicnode.h"

typedef struct Queue
{
        int size;
        BasicNode *head, *tail;
}Queue;

extern Queue *createQueue();
extern void enqueue(Queue *Q, node *val);
extern void enqueueA(Queue *Q,anode *val);
extern node *dequeue(Queue *Q);
extern anode *dequeueA(Queue *Q);
extern int getLength();
extern node *front(Queue *Q);
extern anode *frontA(Queue *Q);

#endif
