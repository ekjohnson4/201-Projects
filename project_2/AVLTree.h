#ifndef AVLTree
#define AVLTree

typedef struct avltree
{
    char *data;
    char *parent;
    char *pos;
    struct avltree *right;
    struct avltree *left;
    int height, count;
}anode;

extern int height(anode *N);
extern int max(int a, int b);
extern int minA(int a, int b);
extern anode *newNodeA(char *key);
extern anode *rightRotate(anode *y);
extern anode *leftRotate(anode *x);
extern int getBalance(anode *N);
extern anode *insertA(anode* node, char *key);
extern anode *minValueNodeA(anode* node);
extern anode *deleteNodeA(anode* root, char *key);
extern char *searchparentA(anode *root, anode *temp);
extern anode *favor(anode *root,char *val);
extern void printLevelOrderA(anode *root);
extern anode *searchTreeA(anode *root, char *val);
extern int countA(anode *root);
extern int minDepthA(anode *root);
extern int maxDepthA(anode *root);

#endif
