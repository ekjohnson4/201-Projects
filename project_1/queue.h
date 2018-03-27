#ifndef QUEUE
#define QUEUE

typedef struct Queue
{
        BasicNode *head;
        BasicNode *tail;
}Queue;

extern Queue *createQueue();
extern void enqueue(Queue *Q, value *val);
extern value *dequeue(Queue *Q);
extern value *front(Queue *Q);
extern int getLength(Queue *Q);
extern int isQueueEmpty(Queue *Q);

#endif
