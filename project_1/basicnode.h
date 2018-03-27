#ifndef BASICNODE
#define BASICNODE

#include "value.h"

typedef struct basicnode
{
        struct basicnode *next;
        value *data;
}BasicNode;

extern BasicNode *NewBasicNode(value *val);

#endif
