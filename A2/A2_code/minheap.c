/**
 *                        Min-Heaps
 * 
 * Please make sure you read the blurb in `minheap.h` to ensure you understand 
 * how we are implementing min-heaps here and what assumptions / requirements 
 * are being made.
 * 
 * (c) Mustafa Quraish, 2021
 */

#include "minheap.h"

/**
 * Allocate a new min heap of the given size.
 * 
 * TODO: 
 *  Allocate memory for the `MinHeap` object, and the 2 arrays inside it.
 *  `numItems` should initially be set to 0, and all the indices should be
 *   set to -1 to start with (since we don't have anything in the heap).
 */
MinHeap *newMinHeap(int size) {
  MinHeap *heapPt = (MinHeap *) malloc(sizeof(MinHeap)); 

  if(heapPt == NULL){
    return NULL;
  }
  heapPt->numItems =0;
  heapPt->maxSize = size;
  heapPt->arr = (HeapElement *) malloc(size*sizeof(HeapElement));


  if ( heapPt->arr == NULL){
    return NULL;
  }

  heapPt->indices = (int *) malloc(size*sizeof(int));
  
  if (heapPt->indices == NULL){
    return NULL;
  }

  for (int i = 0; i < size; i++){
    heapPt->indices[i] = -1;
  }
  return heapPt;
}

/**
 * Swaps elements at indices `a` and `b` in the heap, and also updates their
 * indices. Assumes that `a` and `b` are valid.
 * 
 * NOTE: This is already implemented for you, no need to change anything.
 */

void swap(MinHeap *heap, int a, int b) {
  // Swap the elements
  HeapElement temp = heap->arr[a];
  heap->arr[a] = heap->arr[b];
  heap->arr[b] = temp;

  // Refresh their indices
  heap->indices[heap->arr[a].val] = a;
  heap->indices[heap->arr[b].val] = b;
}

int LeftChildExists(MinHeap *heap, int i){
  if (i*2 + 1 > heap->numItems){
    return -1;
  } else {
    return 1;
  }
}

int RightChildExists(MinHeap *heap, int i){
  if (i*2 + 2 > heap->numItems){
    return -1;
  } else {
    return 1;
  }
}

void percolate(MinHeap *heap, int i){
  int parent = (i-1)/2;

  heap->indices[heap->arr[i].val] = i; 

  if (heap->arr[parent].priority > heap->arr[i].priority){
    swap(heap, parent, i);
    percolate(heap, parent);
  }
}

void heapify(MinHeap *heap, int t){
  int leftInd = 2*t + 1;
  int rightInd = 2*t + 2;
  int minimumInd;

  if (LeftChildExists(heap, t) != -1 && heap->arr[leftInd].priority < heap->arr[t].priority){
    minimumInd = leftInd;
  } else {
    minimumInd = t;
  }
  

  if (RightChildExists(heap, t) != -1 && heap->arr[rightInd].priority < heap->arr[minimumInd].priority){
    minimumInd = rightInd;
  }

  
  if (minimumInd != t){
    swap(heap, minimumInd, t);
    heapify(heap, minimumInd);
  }
  
}
/**
 * Add a value with the given priority into the heap.
 * 
 * TODO: Complete this function, and make sure all the relevant data is updated
 *      correctly, including the `indices` array if you move elements around. 
 *      Make sure the heap property is not violated. 
 * 
 * You may assume the value does not already exist in the heap, and there is
 * enough space in the heap for it.
 */
void heapPush(MinHeap *heap, int val, double priority) {
  HeapElement insElement = {val, priority};

  heap->arr[heap->numItems] = insElement;
  percolate(heap, heap->numItems);
  heap->numItems++;

  return; // Push value to heap before returning
}

/**
 * Extract and return the value from the heap with the minimum priority. Store
 *  the priority for this value in `*priority`. 
 * 
 * For example, if `10` was the value with the lowest priority of `1.0`, then
 *  you would have something that is equivalent to:
 *      
 *        *priority = 1.0;
 *        return 10;
 * 
 * TODO: Complete this function, and make sure all the relevant data is updated
 *      correctly, including the `indices` array if you move elements around. 
 *      Make sure the heap property is not violated. 
 * 
 * You may assume there is at least 1 value in the heap.
 */
int heapExtractMin(MinHeap *heap, double *priority) {
  HeapElement minRoot = heap->arr[0];
  heap->arr[0] = heap->arr[heap->numItems-1];
  heap->indices[heap->arr[0].val] = 0;
  heap->numItems--;
  heapify(heap, 0);


  *priority = minRoot.priority;  // Set correct priority  
  return minRoot.val;         // Return correct value
}

/**
 * Decrease the priority of the given value (already in the heap) with the
 * new priority.
 * 
 * NOTE: You will find it helpful here to first get the index of the value
 *       in the heap from the `indices` array.
 * 
 * TODO: Complete this function, and make sure all the relevant data is updated
 *      correctly, including the `indices` array if you move elements around. 
 *      Make sure the heap property is not violated. 
 * 
 * You may assume the value is already in the heap, and the new priority is
 *  smaller than the old one (caller is responsible for ensuring this).
 */
void heapDecreasePriority(MinHeap *heap, int val, double priority) {
  heap->arr[heap->indices[val]].priority = priority;          // Decrease priority before return
  percolate(heap, heap->indices[val]);
  return;  
}

/**
 * Free the data for the heap. This won't be marked, but it is always good
 * practice to free up after yourself when using a language like C.
 */
void freeHeap(MinHeap *heap) {
  return;   // Free heap and it's arrays
}
