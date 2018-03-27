#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "stdbool.h"
#include "limits.h"

#include "heap.h"

int level = 0;
int nodecount = 0;
bool rec = false;

//Initializes a new node for a heap
MinHeapNode*
newMinHeapNode(int v, int key)
{
    MinHeapNode* heapNode = (MinHeapNode*) malloc(sizeof(MinHeapNode));
    heapNode->v = v;
    heapNode->key = key;
    return heapNode;
}

//Creates a new heap
MinHeap*
newBinHeap(int capacity)
{
    MinHeap* minHeap =
         (MinHeap*) malloc(sizeof(MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
         (MinHeapNode**) malloc(capacity * sizeof(MinHeapNode*));
    return minHeap;
}

// Swaps two nodes of a heap
void
swapMinHeapNode(MinHeapNode** a, MinHeapNode** b)
{
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void
bubbleUp(MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->key < minHeap->array[smallest]->key )
      smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->key < minHeap->array[smallest]->key )
      smallest = right;

    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];

        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        bubbleUp(minHeap, smallest);
    }
}

// A utility function to check if the given minHeap is ampty or not
int
isEmpty(MinHeap* minHeap)
{
    return minHeap->size == 0;
}

// Standard function to extract minimum node from heap
MinHeapNode*
extractBinHeap(MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;

    // Store the root node
    MinHeapNode* root = minHeap->array[0];

    // Replace root with last node
    MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // Update position of last node
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;

    // Reduce heap size and heapify root
    --minHeap->size;
    bubbleUp(minHeap, 0);

    return root;
}

// Decrease key value of vertex v
void
decreaseKeyBinHeap(MinHeap* minHeap, int v, int key)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];

    // Get the node and update its key value
    minHeap->array[i]->key = key;

    // Travel up while the complete tree is not hepified
    while (i && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);

        // move to parent index
        i = (i - 1) / 2;
    }
}

//Checks to see if value is in fact in heap
bool
isInMinHeap(MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}

void sortLevel(int final[],int nodecount,int co) {
  int min = 100000000;
  int min2 = 0;
  int min3 = 0;

  int hold = 0;

  //Sort level from smallest to largest
  for(int o = 0; o<nodecount*3; o++){
    if(final[o]<min){
      min = final[o];
      min2 = final[o+1];
      min3 = final[o+2];

      hold = o;
    }
    o++;
    o++;
  }

  printf("%d(%d)%d, ",min,min2,min3);

  co--;

  final[hold] = 100000000;
  final[hold + 1] = 100000000;
  final[hold + 2] = 100000000;

  hold = 0;

  if(co!=0){
    sortLevel(final,nodecount,co);
  }
}

// A utility function used to print the constructed MST
void
levelOrder(int temp1[], int temp2, int temp3[], int back[]){
    bool negative;
    int arr[temp2];
    int a = 1;
    int v[temp2];
    int b = 1;
    int weight[temp2];
    int c = 1;

    /**************************
    Remove all negative vertices
    ***************************/
    for (int i = 1; i < temp2; ++i){
      //Check if vertex is negative
      negative = temp1[i] < 0;

      if(negative == true){
        continue;
      }
      else{
        arr[a] = temp1[i];
        a++;

        v[b] = i;

        //If this is a recursive call of the function, use back array
        if (rec==true){
          v[b] = back[i];
        }

        b++;

        weight[c] = temp3[i];
        c++;
      }
    }

    int root[temp2];

    /*************
    Assign root
    *************/
    int min_root = arr[1];

    // Loop through arr looking for the min vertex
    for (int j = 2; j < a; j++){
        if (arr[j] < min_root) {
            min_root = arr[j];
        }
    }

    // Loop through v looking for the min vertex
    for (int j = 1; j < a; j++){
        if (v[j] < min_root) {
            min_root = v[j];
        }
    }

    root[1] = min_root;

    /****************
    Print level order
    ****************/
    //Holds current parent for comparing
    int currpar = 1;
    //Holds number that shows how much to increment array for assignment
    int par = 1;
    //Holds how many parents need to be compared on one level
    int parcount = 1;
    //Holds how many parents are on next level
    int partemp = 0;
    //A variable to check how many iterations of one level have been run
    int count = 1;
    //To see if it's time to print level number
    bool l = true;
    //To see if anything printed or not
    bool h = false;
    //Holds weight of tree
    int w = 0;
    //Holds current level
    int level = 0;

    int final[temp2];
    int z = 0;

    printf("%d: %d;\n",level,root[1]);

    level++;

    //Iterate until no more vertices are present
    while(c != 0){
      //Iterate through vertices as many times as needed before prnting newline
      for(int p = 0; p < parcount; p++){
        //Print level number
        if(l == true){
          printf("%d: ",level);
          level++;
          l = false;
        }

        //Iterate through entire vertices collection to find current parent nodes
        for (int i = 1; i < b; ++i){
          //First element matches parent
          if(arr[i] == root[currpar]){
            h = true;

            nodecount++;

            final[z] = v[i];
            z++;
            final[z] = arr[i];
            z++;
            final[z] = weight[i];
            z++;

            //Add weight to weight total
            w = w + weight[i];

            //Add new vertex to parent array
            root[1 + par] = v[i];
            //Increase amount of increment
            par++;
            //Increase number of parents on next level
            partemp++;

            //Change info so they can not be printed or accessed again
            v[i] = -1;
            arr[i] = -1;
            weight[i] = -1;

            //Take away a variable
            c--;
          }

          //Second element matches parent
          else if(v[i] == root[currpar]){
            h = true;

            nodecount++;

            final[z] = arr[i];
            z++;
            final[z] = v[i];
            z++;
            final[z] = weight[i];
            z++;

            //Add weight to weight total
            w = w + weight[i];

            //Add new vertex to parent array
            root[1 + par] = arr[i];
            //Increase amount of increment
            par++;
            //Increase number of parents on next level
            partemp++;

            //Change info so they can not be printed or accessed again
            v[i] = -1;
            arr[i] = -1;
            weight[i] = -1;

            //Take away a variable
            c--;
          }
        }
        //Increment the parent that is being checked
        currpar++;

        //Decrease number of parents that need to be checked
        count--;

        //If no more parents are needed to be checked
        if(count == 0){
          count = partemp;
          parcount = partemp;
          partemp = 0;

          //Toggle l to true in order to print next level number
          l = true;
          //If nothing was printed, erase line and make recursive call
          if(h==false){
            //Check how many chars to delete
            if(level<10){
              printf("\b\b\b");
            }
            else if(level>10 && level<100){
              printf("\b\b\b\b");
            }
            else if(level>100){
              printf("\b\b\b\b\b");
            }

            //Set bool to indicate that next iteration is in fact a recursive call
            rec = true;

            printf("weight: %d\n", w);

            levelOrder(arr,a,weight,v);
          }

          //Prints newline IF things were printed
          else{
            sortLevel(final, nodecount,nodecount);

            nodecount = 0;
            z=0;

            printf("\b\b;\n");

            //Reset bool for indicating whether or not something was printed
            h = false;

            //If there are no more vertices to print, exit
            if (c == 1 || c == 0){
              //Print weight
              printf("weight: %d\n", w);
              exit(0);
            }
          }
        }
      }
    }
}
