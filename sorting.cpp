#include "sorting.h"
#include <iostream> //temporary for debugging

// Temporary for debugging
static void printArray (int array[], int size){
    for (int i=0; i<size; ++i){
        std::cout << array[i];
    }
    std::cout << std::endl;
}

/*------------------------ Static Declarations -------------------------------*/

// Common static functions
static void swap (int array[], unsigned a, unsigned b);
static void arrayCopy (int array[], int arrayCopy[],
    unsigned start, unsigned end);

// Quick sort static functions
static void quickIteration(int array[], unsigned start, unsigned end);
static unsigned quickPartition(int array[], unsigned start, unsigned end);

// Merge sort static functions
static void merger(int array[], int newArray[], unsigned start1,
    unsigned end1, unsigned start2, unsigned end2);
static void mergHelper(int* array[], int* newArray[], 
    unsigned size, unsigned mergLen);
static void merger(int array[], int newArray[], unsigned start1,
    unsigned end1, unsigned start2, unsigned end2);

// Heap sort static functions
static void heapify (int array[], unsigned size);
static void heapShiftup(int array[], unsigned last);
static inline unsigned heapParent(unsigned child);
static inline unsigned heapChildLeft(unsigned parent);
static inline unsigned heapChildRight(unsigned parent);
static void heapShiftdown(int array[], unsigned last);

/*------------------------- Common Functions ---------------------------------*/

// Swap two elements in an array
static void swap (int array[], unsigned a, unsigned b){
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

// Copy an array from start to < end
static void arrayCopy (int array[], int arrayCopy[],
    unsigned start, unsigned end){
    for (int i=start; i<end; ++i){
        arrayCopy[i] = array[i];
    }
}

/*--------------------------- Quick Sort -------------------------------------*/

// Recursive quick sort (note variable 'end' is inclusive)
static void quickIteration(int array[], unsigned start, unsigned end){
    unsigned pivot;
    // Recursive quick sort until only one element left
    if (start < end){
        // Find pivot
        pivot = quickPartition(array, start, end);
        // Recursive quick sort left side
        quickIteration(array, start, pivot);
        // Recursive quick sort right side
        quickIteration(array, pivot+1, end);
    }
}

// Partition the array and return pivot point
//      (note variable 'end' is inclusive)
static unsigned quickPartition(int array[], unsigned start, unsigned end){
    int pivot = array[start];
    unsigned i = start;
    unsigned j = end;
    // Swap elements < pivot with elements > pivot and return the pivot point
    for (;;){
        while (array[i] < pivot) ++i;
        while (array[j] > pivot) --j;
        if (i >=j) return j;
        swap(array, i, j);
        ++i;
        --j;
    }
}

// Quick sort main function
void quickSort(int array[], unsigned size){
    // Start recursive quicksort with the whole array
    quickIteration(array, 0, size-1);
}

/*------------------------------ Merge Sort ----------------------------------*/

// Merge two sections of the array into an new merged sorted section
static void merger(int array[], int newArray[], unsigned start1,
    unsigned end1, unsigned start2, unsigned end2){
    unsigned i=start1, i1=start1, i2=start2;
    // Merge the 2 sections of the array until one section is finished
    for (i; (i1<end1)&&(i2<end2); ++i){
        if (array[i1]<array[i2]){
            newArray[i]=array[i1];
            ++i1;
        }else{
            newArray[i]=array[i2];
            ++i2;
        }
    } 
    // Fill the rest with the unfinished section
    for (i1; i1<end1; ++i1, ++i){
       newArray[i] = array[i1];
    }
    for (i2; i2<end2; ++i2, ++i){
       newArray[i] = array[i2];
    }
}

// Run one iteration of merge sort according to the merge length
static void mergHelper(int* array[], int* newArray[],
    unsigned size, unsigned mergLen){
    unsigned pieces = size/mergLen;
    pieces += (size%mergLen)?1:0; 
    bool oddPieces = pieces&((unsigned)1);
    unsigned mergTo = ((oddPieces)?(pieces-1):(pieces))*mergLen;
    unsigned i, a2start, a1end, a2end;
    int* temp = *array;
    // Break array into pieces of combined merged length
    for (i=0; i<mergTo; i+=(mergLen<<1)){
        a2start = i+mergLen;
        a1end = a2start;
        a2end = a2start+mergLen;
        a2end = (a2end>size)?size:a2end;
        merger(*array, *newArray, i, a1end, a2start, a2end);
    }
    arrayCopy(*array, *newArray, mergTo, size);
    *array = *newArray;
    *newArray = temp;    
}

// Merge sort main function
void mergSort(int array[], unsigned size){
    int* tempArray = new int[size];
    int* sorted = array;
    int* unsorted = tempArray;
    // Perform merge algorithm until merge length is greater than array size
    for (unsigned i=1; i < size; i<<=1){
        mergHelper(&sorted, &unsorted, size, i);
    }
    if (unsorted == array)
        arrayCopy(tempArray, array, 0, size);
    delete[] tempArray;
}

/*------------------------------ Heap Sort -----------------------------------*/

// Get parent of a given index in a heap
static inline unsigned heapParent(unsigned child){
    return ((child-1)>>1);
}

// Get left child of a given index in a heap
static inline unsigned heapChildLeft(unsigned parent){
    return ((parent<<1)+1);
}

// Get right child of a given index in a heap
static inline unsigned heapChildRight(unsigned parent){
    return ((parent<<1)+2);
}

// Insert element into heap
static void heapShiftup(int array[], unsigned last){
    unsigned parent = heapParent(last);
    // Shift up new element to correct place in heap
    while((last)&&(array[last]>array[parent])){
        swap(array, last, parent);
        last = parent;
        parent = heapParent(last);
    }
}

// Convert array into heap
static void heapify (int array[], unsigned size){
    // Heapify by shifting up all the elements in the heap
    for (unsigned i=1; i < size; ++i) heapShiftup(array, i);
}

// Convert heap into a sorted array
static void heapShiftdown(int array[], unsigned last){
    unsigned parent = 0;
    unsigned leftChild = heapChildLeft(parent);
    unsigned rightChild = heapChildRight(parent);
    unsigned greater;
    // Shift down until both left and right children are less than current 
    //      or until current has no right child 
    while(leftChild < last){
        greater = leftChild;
        if (rightChild < last && array[rightChild] > array[leftChild])
            greater = rightChild;
        if (array[greater] > array[parent]){
            swap(array, greater, parent);
            parent = greater;
        }else return;
        leftChild = heapChildLeft(parent);
        rightChild = heapChildRight(parent);
    }
}

// Heap sort main function
void heapSort(int array[], unsigned size){
    // Heapify array
    heapify(array, size);
    // Swap the top (max) of heap with the end of heap and reduce heap size,
    //      then shift down the swaped element at the top to the right place
    //      repeat until heap is turned into a sorted array
    for (unsigned last=(size-1); last > 0; --last){
        swap(array, 0, last);
        heapShiftdown(array, last);
    }
}

/*--------------------------------- END --------------------------------------*/

