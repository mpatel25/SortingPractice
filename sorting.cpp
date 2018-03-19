#include "sorting.h"

static bool compare (int a, int b);
static void swap (int array[], unsigned a, unsigned b);

static void quickIteration(int array[], unsigned start, unsigned end);
static int quickPartition(int array[], unsigned start, unsigned end);

static bool compare (int a, int b){
    return a < b;
}

static void swap (int array[], unsigned a, unsigned b){
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

static void quickIteration(int array[], unsigned start, unsigned end){
    unsigned pivot;
    if (start < end){
        pivot = quickPartition(array, start, end);
        quickIteration(array, start, pivot);
        quickIteration(array, pivot+1, end);
    }
}

static int quickPartition(int array[], unsigned start, unsigned end){
    unsigned pivot = start;
    unsigned i = start;
    unsigned j = end;
    for(;;){
        while (array[i] < array[pivot]) i++;
        while (array[j] > array[pivot]) j--;
        if (i >=j) return j;
        swap(array, i, j);
    }
}

void quickSort(int array[], unsigned size){
    quickIteration(array, 0, size-1);
}

void mergSort(int array[], unsigned size){

}

void timSort(int array[], unsigned size){

}

void heapSort(int array[], unsigned size){

}

