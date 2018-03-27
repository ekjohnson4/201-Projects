#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "stack.h"

Stack
*createStack()
{
  /* Create a Stack */
  Stack *S = (Stack *)malloc(sizeof(Stack));
  S->head=0;
  S->top=-1;
  return S;
}

value
*pop(Stack *S)
{
  if (S->head == NULL) {
    return NULL;
  }

  value *temp = S->head->data;
  S->head = S->head->next;
  S->top--;
  return temp;
}

value
*top(Stack *S)
{
    return S->head->data;
}

int
topI(Stack *S)
{
    return S->head->data->ival;
}

double
topR(Stack *S)
{
    return S->head->data->rval;
}

int
isEmpty(Stack *S){
  if (S->top == -1){
    return 1;
  }
  else{
    return 0;
  }
}

void
push(Stack *S, value *element)
{
  BasicNode *x = NewBasicNode(element);
  x->next = S->head;
  S->head = x;
  S->top++;
}

// A utility function to return precedence of a given operator
// Higher returned value means higher precedence
int
Prec(value *ch)
{
    switch (*ch->sval)
    {
    case '+':
        return 1;
    case '-':
        return 2;

    case '*':
        return 3;
    case '/':
        return 4;

    case '%':
        return 5;

    case '^':
        return 6;
    }
    return -1;
}
