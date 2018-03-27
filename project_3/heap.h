#ifndef HEAP
#define HEAP

typedef struct heapnode {
  int v, key;
} MinHeapNode;

typedef struct heap {
  int size, capacity, *pos;
  MinHeapNode **array;
} MinHeap;

extern MinHeapNode* newMinHeapNode(int v, int key);
extern MinHeap* newBinHeap(int capacity);
extern void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b);
extern void bubbleUp(MinHeap* minHeap, int idx);
extern int isEmpty(MinHeap* minHeap);
extern MinHeapNode* extractBinHeap(MinHeap* minHeap);
extern void decreaseKeyBinHeap(MinHeap* minHeap, int v, int key);
extern bool isInMinHeap(MinHeap *minHeap, int v);
extern void sortLevel(int final[],int nodecount,int co);
extern void levelOrder(int arr[], int n, int weight[], int back[]);

#endif
