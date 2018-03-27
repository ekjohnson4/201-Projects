#include <stdlib.h>
#include <stdio.h>

#include "treenode.h"

TreeNode
*NewTreeNode(value *dat){
  /*Create new tree node*/
	TreeNode *newTreeNode = malloc(sizeof(TreeNode));

	newTreeNode->parent = NULL;
	newTreeNode->right = NULL;
	newTreeNode->left = NULL;
  newTreeNode->val = dat->val;
	newTreeNode->data = dat->sval;
  newTreeNode->type = dat->type;

	return newTreeNode;
}

TreeNode
*insertElement(TreeNode *node, value *dat){
    //insert element to Tree
    if(node==NULL){
        return NewTreeNode(dat);
    }
    else{
        if(dat->ival > node->val){
            node->left = insertElement(node->left, dat);
            return node;
        }
        else if(dat->ival < node->val){
            node->right =  insertElement(node->right, dat);
            return node;
        }
        else if(dat->sval == node->data){
            node = insertElement(node,dat);
        }
    }
}

TreeNode
*Find(TreeNode *node, char *data, int size){
        if(size == 0) {
          /* Element is not found */
          printf("variable %s was not declared",data[0]);
          exit(0);
          return NULL;
        }

        if(data[0] < node->data[0]){
          /* Search in the right sub tree. */
          size--;
          return Find(node->right,data,size);
        }

        else if(data[0] > node->data[0]){
          /* Search in the left sub tree. */
          size--;
          return Find(node->left,data,size);
        }

        else if (data[0] == node->data[0]){
          /* Element Found */
          node->type = INTEGER;
          size--;
          return node;
        }
}

TreeNode
*Check(TreeNode *node, value *data, int size){
        if(size == 0) {
          /* Element is not found */
          printf("variable %c was not declared",data[0]);
          exit(0);
          return NULL;
        }

        if(data->sval[0] < node->data[0]){
          /* Search in the right sub tree. */
          size--;
          return Check(node->right,data,size);
        }

        else if(data->sval[0] > node->data[0]){
          /* Search in the left sub tree. */
          size--;
          return Check(node->left,data,size);
        }

        else if (data->sval[0] == node->data[0]){
          /* Element Found */
          node->type = INTEGER;
          size--;
          return node;
        }
}

TreeNode
*Change(TreeNode *node, value *data, int size, int dat){
        if(size == 0) {
          /* Element is not found */
          printf("variable %c was not declared",data[0]);
          exit(0);
          return NULL;
        }

        if(data->sval[0] < node->data[0]){
          /* Search in the right sub tree. */
          size--;
          return Change(node->right,data,size,dat);
        }

        else if(data->sval[0] > node->data[0]){
          /* Search in the left sub tree. */
          size--;
          return Change(node->left,data,size,dat);
        }

        else if (data->sval[0] == node->data[0]){
          /* Element Found */
          node->val = dat;
          node->type = INTEGER;
          size--;
          return node;
        }
}
