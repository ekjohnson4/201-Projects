#ifndef BASICNODE
#define BASICNODE

typedef struct basicnode
{
        struct basicnode *next, *prev, *head;
        int data, weight;
}BasicNode;

extern BasicNode *newBasicNode(int data, int weight);

#endif
