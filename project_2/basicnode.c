#include <stdlib.h>
#include <stdio.h>

#include "basicnode.h"

BasicNode
*NewBasicNode(node *data){
	/*Create new basic node*/
	BasicNode *newBasicNode = malloc(sizeof(BasicNode));

	newBasicNode->next = 0;
	newBasicNode->data = data;

	return newBasicNode;
}

BasicNode
*NewBasicNodeA(anode *data){
	/*Create new basic node*/
	BasicNode *newBasicNode = malloc(sizeof(BasicNode));

	newBasicNode->next = 0;
	newBasicNode->dataA = data;

	return newBasicNode;
}
