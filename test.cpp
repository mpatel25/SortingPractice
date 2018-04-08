#include "sorting.h"
#include <iostream>

int main (int argc, char* argv[]){
    int testArray[] = {1, 4, 2, 2, 5};
    for (int i=0; i<5; ++i)
        std::cout << testArray[i];
    std::cout << std::endl;
    heapSort(testArray, 5);
    for (int i=0; i<5; ++i)
        std::cout << testArray[i];
    std::cout << std::endl;
    return 0;
}

