#ifndef STACK
#define STACK

#include "queue.h"

typedef struct Stack
{
    int top;
    BasicNode *head;
}Stack;

extern Stack * createStack();
extern value *pop(Stack *S);
extern value *top(Stack *S);
extern int topI(Stack *S);
extern double topR(Stack *S);
extern value *frontNode(Stack *S);
extern void push(Stack *S, value *element);
extern int Prec(value *ch);
extern int isEmpty(Stack *S);

#endif
