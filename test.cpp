#include "sorting.h"
#include <iostream>

int main (int argc, char* argv[]){
    int testArray[] = {5, 4, 3, 2, 1};
    for (int i=0; i<5; ++i)
        std::cout << testArray[i];
    std::cout << std::endl;
    quickSort(testArray, 5);
    for (int i=0; i<5; ++i)
        std::cout << testArray[i];
    std::cout << std::endl;
    return 0;
}

