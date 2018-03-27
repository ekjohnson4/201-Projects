#ifndef SUPPORT
#define SUPPORT

#include "basicnode.h"

typedef struct graph
{
        BasicNode *array;
        int V;
}Graph;

extern Graph *createGraph(int V);
extern void addEdge(Graph* graph, int src, int dest, int weight);

#endif
