#include <stdio.h>
#include <stdlib.h>

#include "support.h"

Graph*
createGraph(int V)
{
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->V = V;

    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (BasicNode*) malloc(V * sizeof(BasicNode));

     // Initialize list
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Adds an edge to an undirected graph
void
addEdge(Graph* graph, int src, int dest, int weight)
{
    // Add an edge to dest.
    BasicNode* newNode = newBasicNode(dest, weight);
    //Add new node to beginning of list
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Add edge from dest to src
    newNode = newBasicNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
