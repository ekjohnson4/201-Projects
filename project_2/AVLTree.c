#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

#include "AVLTree.h"
#include "queue.h"

// A utility function to get height of the tree
int
height(anode *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum of two integers
int
max(int a, int b)
{
    return (a > b)? a : b;
}

// A utility function to get maximum of two integers
int
minA(int a, int b)
{
    return (a < b)? a : b;
}

anode *
newNodeA(char *key)
{
    anode* node = (anode*)malloc(sizeof(anode));
    node->data   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;
    node->count = 1;
    return(node);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
anode *
rightRotate(anode *y)
{
    anode *x = y->left;
    anode *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
anode *
leftRotate(anode *x)
{
    anode *y = x->right;
    anode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int
getBalance(anode *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

anode *
insertA(anode* node, char *key)
{
    /* 1.  Perform the normal BST rotation */
    if (node == NULL)
        return (newNodeA(key));

    int com = 0;
    com = strcmp(key,node->data);

     /* Otherwise, recur down the tree */
    if (com < 0){
        node->left  = insertA(node->left, key);
      }
    else if(com > 0){
        node->right = insertA(node->right, key);
      }
    else{
      node->count++;
    }

    /* 2. Update height of this ancestor node */
    node->height = max(height(node->left), height(node->right)) + 1;

    /* 3. Get the balance factor of this ancestor node to check whether
       this node became unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && strcmp(key,node->left->data) < 0)
        return rightRotate(node);

    // Left Right Case
    if (balance > 1 && strcmp(key,node->left->data) > 0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Right Case
    if (balance < -1 && strcmp(key,node->right->data) > 0)
        return leftRotate(node);

    // Right Left Case
    if (balance < -1 && strcmp(key,node->right->data) < 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

anode *
minValueNodeA(anode* node)
{
    anode* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

anode *
deleteNodeA(anode* root, char *key)
{
    // STEP 1: PERFORM STANDARD BST DELETE

    if (root == NULL) return root;

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if ( strcmp(key,root->data) < 0)
        root->left = deleteNodeA(root->left, key);

    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if( strcmp(key,root->data) > 0)
        root->right = deleteNodeA(root->right, key);

    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
      // If key is present more than once, simply decrement
      // count and return
      if (root->count > 1)
      {
          (root->count)--;
          return root;
      }
      // ElSE, delete the node

      // node with only one child or no child
      if( (root->left == NULL) || (root->right == NULL) )
      {
          anode *temp = root->left ? root->left : root->right;

          // No child case
          if(temp == NULL)
          {
              temp = root;
              root = NULL;
              free(temp);
          }
          else{ // One child case
              anode *temp1=root;
              root=temp;
              free(temp1);
            }
      }
      else
      {
          // node with two children: Get the inorder successor (smallest
          // in the right subtree)
          anode* temp = minValueNodeA(root->right);

          // Copy the inorder successor's data to this node
          root->data = temp->data;

          root->count = temp->count;

          temp->count=1;
          // Delete the inorder successor
          root->right = deleteNodeA(root->right, temp->data);
      }
    }

    // If the tree had only one node then return
    if (root == NULL)
      return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    root->height = max(height(root->left), height(root->right)) + 1;

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether
    //  this node became unbalanced)
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

char *
searchparentA(anode *root, anode *temp)
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
        return searchparentA(root->right, temp);
    }

    else if(key > 0)
    {
        return searchparentA(root->left, temp);
    }
}

anode *
favor(anode *root, char *val)
{
  int key = 0;
  key = strcmp(val,root->data);

  // Base Cases: root is null or key is present at root
  if (root == NULL || key == 0){
    if (root==NULL)
        return 0;
    else
    {
        /* compute the depth of each subtree */
        int lDepth = maxDepthA(root->left);
        int rDepth = maxDepthA(root->right);

        /* use the larger one */
        if (lDepth > rDepth){
            printf("-");
          }
        else if (lDepth <rDepth){
            printf("+");
        }
        else{
          printf("");
        }
    }
    return root;
  }

  // Key is greater than root's key
  if (key > 0)
    return favor(root->right, val);

  // Key is smaller than root's key
  return favor(root->left, val);
}

// Iterative method to do level order traversal line by line
void
printLevelOrderA(anode *root)
{
    //variable holds current level
    int l = 0;

    // Base Case
    if (root == NULL)  return;

    // Create an empty queue for level order tarversal
    Queue *Q = createQueue();

    // Enqueue Root and initialize height
    enqueueA(Q,root);

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

            anode *node = frontA(Q);

            /***************
                LEAF
            ***************/
            if (node->left == NULL && node->right == NULL){
              printf("=%s",node->data);
              favor(root,node->data);

              //If root, print root as parent
              if(l==1){
                printf("(%s",node->data);
                favor(root,node->data);
                printf(")");
              }

              //Else print actual parent
              else{
                node->parent = searchparentA(root,node);
                printf("(%s",node->parent);
                favor(root,node->parent);
                printf(")");
              }

              //Print occurences
              printf("%d",node->count);

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
              favor(root,node->data);

              //If root, print root as parent
              if(l==1){
                printf("(%s",node->data);
                favor(root,node->data);
                printf(")");
              }
              //Else print actual parent
              else{
                node->parent = searchparentA(root,node);
                printf("(%s",node->parent);
                favor(root,node->parent);
                printf(")");
              }

              //Print occurences
              printf("%d",node->count);

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

            dequeueA(Q);
            if (node->left != NULL)
                enqueueA(Q,node->left);
            if (node->right != NULL)
                enqueueA(Q,node->right);
            nodeCount--;
        }
        printf("\n");
    }
}

anode *
searchTreeA(anode *root, char *val){
  // Base Cases: root is null or key is present at root
  if (root->data == NULL || strcmp(val,root->data) == 0){
    printf("Frequency of '%s' is %d\n",root->data,root->count);
    return root;
  }

  // Key is greater than root's key
  if (strcmp(val,root->data) > 0){
    if(root->right==NULL){
      printf("Frequency of '%s' is 0\n",val);
      return root;
    }
    else{
    return searchTreeA(root->right, val);
    }
  }

  // Key is smaller than root's key
  if(root->left==NULL){
    printf("Frequency of '%s' is 0\n",val);
    return root;
  }
  else{
    return searchTreeA(root->left, val);
  }
}

int
countA(anode *root)
{
    int c = 1;

    if (root == NULL)
        return 0;
    else
    {
        c += countA(root->left);
        c += countA(root->right);
        return c;
     }
}

int
minDepthA(anode *root)
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
       return minDepthA(root->right) + 1;

    // If right subtree is NULL, recur for right subtree
    if (!root->right)
       return minDepthA(root->left) + 1;

    return minA(minDepthA(root->left), minDepthA(root->right)) + 1;
}

int
maxDepthA(anode *root)
{
   if (root==NULL)
       return 0;
   else
   {
       /* compute the depth of each subtree */
       int lDepth = maxDepthA(root->left);
       int rDepth = maxDepthA(root->right);

       /* use the larger one */
       if (lDepth > rDepth)
           return(lDepth+1);
       else return(rDepth+1);
   }
}
