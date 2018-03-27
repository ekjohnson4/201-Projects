#ifndef TREENODE
#define TREENODE

#include "basicnode.h"

typedef struct treenode
{
        struct treenode *left;
        struct treenode *right;
        struct treenode *parent;
        char *data;
        int val;
        char *type;
}TreeNode;

extern TreeNode *NewTreeNode(value *dat);
extern TreeNode *insertElement(TreeNode *node, value *dat);
extern TreeNode *Find(TreeNode *node, char *data, int size);
extern TreeNode *Check(TreeNode *node, value *data, int size);
extern TreeNode *Change(TreeNode *node, value *data, int size, int dat);

#endif
