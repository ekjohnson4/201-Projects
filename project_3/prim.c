/*
Author: Ethan Johnson
Class: CS 201
Fall 2016
*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "ctype.h"
#include "limits.h"

#include "support.h"
#include "heap.h"
#include "scanner.h"

int optionD = 0;

void
PrimMST(Graph* graph)
{
    int V = graph->V;
    int parent[V];
    int key[V];
    int weight[V];
    int back[V];

    // Create new minHeap
    MinHeap* minHeap = newBinHeap(V);

    // Initialize min heap with all vertices
    for (int v = 1; v < V; ++v)
    {
        parent[v] = -1;
        key[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, key[v]);
        minHeap->pos[v] = v;
    }

    // Make key of the root 0
    key[0] = 0;
    minHeap->array[0] = newMinHeapNode(0, key[0]);
    minHeap->pos[0]   = 0;

    minHeap->size = V;

    while (!isEmpty(minHeap))
    {
        // Extract the vertex with minimum key value and store it
        MinHeapNode* minHeapNode = extractBinHeap(minHeap);
        int u = minHeapNode->v;

        // Traverse through all adjacent vertices of u
        BasicNode* pCrawl = graph->array[u].head;

        while (pCrawl != NULL)
        {
            int v = pCrawl->data;

            if (isInMinHeap(minHeap, v) && pCrawl->weight < key[v])
            {
                key[v] = pCrawl->weight;

                parent[v] = u;

                weight[v] = pCrawl->weight;

                decreaseKeyBinHeap(minHeap, v, key[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

    // prints edges in level order
    levelOrder(parent, V, weight, back);
}

int
getMax(FILE *file){
  int count = 0;

  //Check and see if file is empty
  if (file == NULL){
    printf("File empty!");
  }

  //Count how many semicolons appear
  while(1){
    readToken(file);
    readToken(file);
    char *c = readToken(file);

    if(feof(file)){
      break;
    }

    if(strcmp(c, ";")){
      count++;

      //Read the semicolon to skip in next iteration
      readToken(file);
    }
    else{
      continue;
    }
  }
  return count;
}

int
main(int argc,char **argv) {
  //Check to see if user has implemented all necessary arguments
  if (argc != 2){
    printf("Need two arguments!");
    return EXIT_FAILURE;
  }

  //Open file
	FILE* file1 = fopen(argv[1], "r");

  int max = getMax(file1);

  //Open file
  FILE* file = fopen(argv[1], "r");

  //Check and see if file is empty
  if (file == NULL){
    printf("File empty!");
  }

  int V = max + 3;

  Graph* graph = createGraph(V);

  while(1){
    char *a = readToken(file);
    char *b = readToken(file);
    char *c = readToken(file);

    if(feof(file)){
      break;
    }

    if(strcmp(c, ";")){
      int x = atoi(a);
      int y = atoi(b);
      int z = atoi(c);

      //Read the semicolon to skip in next iteration
      readToken(file);

      addEdge(graph,x,y,z);
    }
    else{
      int x = atoi(a);
      int y = atoi(b);
      int z = 1;

      addEdge(graph,x,y,z);
    }
  }

  //Run graph through Prim's
  PrimMST(graph);

  return 0;
}
