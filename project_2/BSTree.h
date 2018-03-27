#ifndef BSTree
#define BSTree

typedef struct bstree
{
    int occ;
    char *data;
    char *pos;
    char *parent;
    struct bstree *right;
    struct bstree *left;
}node;

extern node *newNode(char *item);
extern int min(int a, int b);
extern node *insert(node *node, char *val);
extern node *deleteNode(node* root, char *val);
extern node *minValueNode(node* node);
extern void printLevelOrder(node *root);
extern char *searchparent(node *root, node *temp);
extern node *searchTree(node *root, char *val);
extern int count(node *root);
extern int minDepth(node *root);
extern int maxDepth(node *root);

#endif
