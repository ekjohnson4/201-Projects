#include<stdio.h>
#include<stdlib.h>

#include "queue.h"

int length;

Queue
*createQueue()
{
        /* Create a Queue */
        Queue *Q = (Queue *)malloc(sizeof(Queue));
        Q->head=NULL;
        Q->tail=NULL;
        return Q;
}

value
*dequeue(Queue *Q)
{
      value *temporary = Q->head->data;
      Q->head = Q->head->next;
      length--;
      return temporary;
}

value
*front(Queue *Q)
{
      return Q->head->data;
}

int
getLength(Queue *Q){
      return length;
}

void
enqueue(Queue *Q,node *val)
{
  BasicNode *x = NewBasicNode(val);
      if (Q->head==NULL){
        Q->head=x;
        Q->tail=x;
        length++;
      }
      else{
        Q->tail->next=x;
        Q->tail=x;
        length++;
      }
}

int
isQueueEmpty(Queue *Q){
  return (Q->head==NULL);
}
