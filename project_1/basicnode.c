#include <stdlib.h>
#include <stdio.h>

#include "basicnode.h"

BasicNode
*NewBasicNode(value *val){
	/*Create new basic node*/
	BasicNode *newBasicNode = malloc(sizeof(BasicNode));

	newBasicNode->next = NULL;
	newBasicNode->data = val;

	return newBasicNode;
}
