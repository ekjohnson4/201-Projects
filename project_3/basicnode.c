#include <stdlib.h>
#include <stdio.h>

#include "basicnode.h"

BasicNode*
newBasicNode(int data, int weight)
{
    BasicNode* newNode =
            (BasicNode*) malloc(sizeof(BasicNode));
    newNode->data = data;
    newNode->weight = weight;
    newNode->next = NULL;
		newNode->prev = NULL;
    return newNode;
}
