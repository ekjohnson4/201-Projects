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

node
*dequeue(Queue *Q)
{
      node *temporary = Q->head->data;
      Q->head = Q->head->next;
      length--;
      return temporary;
}

anode
*dequeueA(Queue *Q)
{
      anode *temporary = Q->head->dataA;
      Q->head = Q->head->next;
      length--;
      return temporary;
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

void
enqueueA(Queue *Q,anode *val)
{
  BasicNode *x = NewBasicNodeA(val);
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
getLength(){
      return length;
}

node
*front(Queue *Q)
{
      return Q->head->data;
}

anode
*frontA(Queue *Q)
{
      return Q->head->dataA;
}
