#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

#include "BSTree.h"
#include "queue.h"

// A utility function to create a new BST node
node *
newNode(char *item)
{
    node *temp =  (node *)malloc(sizeof(node));
    temp->data = item;
    temp->parent = item;
    temp->left = temp->right = NULL;
    temp->pos = "X";
    temp->occ = 1;
    return temp;
}

// A utility function to get maximum of two integers
int
min(int a, int b)
{
    return (a < b)? a : b;
}

char *
searchparent(node *root, node *temp)
{
    int key = 0;
    key = strcmp(root->data,temp->data);

    if(root->left != NULL && root->left == temp)
    {
        return root->data;
    }

    else if(root->right != NULL && root->right == temp)
    {
        return root->data;
    }

    else if(key < 0)
    {
        return searchparent(root->right, temp);
    }

    else if(key > 0)
    {
        return searchparent(root->left, temp);
    }
}

node *
insert(node *node, char *val)
{
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(val);

    int key = 0;
    key = strcmp(val,node->data);

    if(key < 0)
    {
        node->left = insert(node->left, val);
    }
    else if(key > 0)
    {
        node->right = insert(node->right, val);
    }
    else{
      node->occ++;
    }

    return node;
}

node *
deleteNode(node* root, char *val)
{
    // base case
    if (root == NULL) return root;

    int key = 0;
    key = strcmp(val,root->data);

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (key < 0){
        root->left = deleteNode(root->left, val);
      }

    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > 0){
        root->right = deleteNode(root->right, val);
      }

    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        root->occ--;
        // node with only one child or no child
        if (root->left == NULL)
        {
            node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            node *temp = root->left;
            free(root);
            return temp;
        }

        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        node* temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

node *
minValueNode(node* current)
{
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Iterative method to do level order traversal line by line
void
printLevelOrder(node *root)
{
    //variable holds current level
    int l = 0;

    // Base Case
    if (root == NULL)  return;

    // Create an empty queue for level order tarversal
    Queue *Q = createQueue();

    // Enqueue Root and initialize height
    enqueue(Q,root);

    //For comparing the parent and child to determine L, R, or X
    int key = 0;

    while (1)
    {
        // nodeCount (queue size) indicates number of nodes
        // at current lelvel.
        int nodeCount = getLength();

        //Indicates total number of nodes within single level
        int max = getLength();

        if (nodeCount == 0)
            break;

        printf("%d: ",l);
        l++;

        // Dequeue all nodes of current level and Enqueue all
        // nodes of next level
        while (nodeCount > 0)
        {
            //print the row number
            if (max == 0){
              printf("%d: ",l);
              l++;
            }

            node *node = front(Q);

            /***************
                LEAF
            ***************/
            if (node->left == NULL && node->right == NULL){
              printf("=%s",node->data);

              //If root, print root as parent
              if(l==1){
                printf("(%s)",node->data);
              }

              //Else print actual parent
              else{
                node->parent = searchparent(root,node);
                printf("(%s)",node->parent);
              }

              //Print occurences
              printf("%d",node->occ);

              //If root, print X
              if(l==1){
                node->pos="X";
                printf("%s ",node->pos);
              }

              //else, compare parent and child and determine if it's left or right
              else{
                key = strcmp(node->data,node->parent);
                if(key<0){
                  node->pos = "L";
                }
                else{
                  node->pos = "R";
                }
                printf("%s ",node->pos);
              }
            }

            /***************
              NOT A LEAF
            ***************/
            else{
              printf("%s",node->data);

              //If root, print root as parent
              if(l==1){
                printf("(%s)",node->data);
              }
              //Else print actual parent
              else{
                node->parent = searchparent(root,node);
                printf("(%s)",node->parent);
              }

              //Print occurences
              printf("%d",node->occ);

              //If root, print X
              if(l==1){
                node->pos="X";
                printf("%s ",node->pos);
              }
              //else, compare parent and child and determine if it's left or right
              else{
                key = strcmp(node->data,node->parent);
                if(key<0){
                  node->pos = "L";
                }
                else{
                  node->pos = "R";
                }
                printf("%s ",node->pos);
              }
            }

            dequeue(Q);
            if (node->left != NULL)
                enqueue(Q,node->left);
            if (node->right != NULL)
                enqueue(Q,node->right);
            nodeCount--;
        }
        printf("\n");
    }
}

node *
searchTree(node *root, char *val){
    // Base Cases: root is null or key is present at root
    if (root->data == NULL || strcmp(val,root->data) == 0){
      printf("Frequency of '%s' is %d\n",root->data,root->occ);
      return root;
    }

    // Key is greater than root's key
    if (strcmp(val,root->data) > 0){
      if(root->right==NULL){
        printf("Frequency of '%s' is 0\n",val);
        return root;
      }
      else{
      return searchTree(root->right, val);
      }
    }

    // Key is smaller than root's key
    if(root->left==NULL){
      printf("Frequency of '%s' is 0\n",val);
      return root;
    }
    else{
      return searchTree(root->left, val);
    }
}

int
count(node *root)
{
    int c = 1;

    if (root == NULL)
        return 0;
    else
    {
        c += count(root->left);
        c += count(root->right);
        return c;
     }
}

int
minDepth(node *root)
{
    // Corner case. Should never be hit unless the code is
    // called on root = NULL
    if (root == NULL)
        return 0;

    // Base case : Leaf Node. This accounts for height = 1.
    if (root->left == NULL || root->right == NULL)
       return 1;

    // If left subtree is NULL, recur for right subtree
    if (!root->left)
       return minDepth(root->right) + 1;

    // If right subtree is NULL, recur for right subtree
    if (!root->right)
       return minDepth(root->left) + 1;

    return min(minDepth(root->left), minDepth(root->right)) + 1;
}

int
maxDepth(node *root)
{
   if (root==NULL)
       return 0;
   else
   {
       /* compute the depth of each subtree */
       int lDepth = maxDepth(root->left);
       int rDepth = maxDepth(root->right);

       /* use the larger one */
       if (lDepth > rDepth)
           return(lDepth+1);
       else return(rDepth+1);
   }
}
