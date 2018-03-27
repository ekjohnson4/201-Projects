#ifndef BASICNODE
#define BASICNODE

#include "BSTree.h"
#include "AVLTree.h"

typedef struct basicnode
{
        struct basicnode *next;
        node *data;
        anode *dataA;
}BasicNode;

extern BasicNode *NewBasicNode(node *data);
extern BasicNode *NewBasicNodeA(anode *data);

#endif
