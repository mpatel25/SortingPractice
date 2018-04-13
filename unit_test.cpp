#include "sorting.h"
#include <gtest/gtest.h>
#include <iostream>

/*------------------------ Static Declarations -------------------------------*/

static void copyArray(int array[], int newArray[], unsigned index);
static void printArray(int array[], unsigned size);
static void swap(int array[], unsigned a, unsigned b);
static void permuteHelper(int array[], int* permutations[],
    unsigned* p_permuteIndex, unsigned at, unsigned size);
static int** permuteArray (int array[], unsigned size);
static void freePermuteArray(int** permutations, unsigned size);
static unsigned factorial (unsigned i);

/*-------------------- Common Functions Definitions --------------------------*/

// The following are helper function to help during testing

// To copy one array into another of the same size
static void copyArray(int array[], int newArray[], unsigned index){
    for (index; index>0; --index)
        newArray[index-1] = array[index-1];
}

// To print an Array to stdout (only for debugging)
static void printArray(int array[], unsigned size){
    std::cout << "[";
    for (unsigned i=0; i<size; ++i){
        std::cout << array[i];
        if (i != (size-1)) std::cout << ", ";
    }
    std::cout << "]\n";
}

// To swap two elements in an array
static void swap(int array[], unsigned a, unsigned b){
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

// Helper function of permuteArray function
static void permuteHelper(int array[], int* permutations[],
    unsigned* p_permuteIndex, unsigned at, unsigned size){
    if (at == (size-1)){
        copyArray(array, permutations[*p_permuteIndex], size);
        ++(*p_permuteIndex);
        return;
    }
    for (unsigned i=at; i<size; ++i){
        swap(array, at, i);
        permuteHelper(array, permutations, p_permuteIndex, (at+1), size);
        swap(array, at, i);
    }
}

// Generates all permutations of an array
// Note: This algo dosen't count for duplicate Elements,
//      therefore repeated permutations
static int** permuteArray (int array[], unsigned size){
    unsigned numPermutations = factorial(size);
    unsigned permuteIndex  = 0;
    int** permutations = new int* [numPermutations];
    for (unsigned i=0; i<numPermutations; ++i){
        permutations[i] = new int [size];
    }
    permuteHelper(array, permutations, &permuteIndex, 0, size);
    return permutations;
}

// To clear the dynamically allocated permutations array
static void freePermuteArray(int** permutations, unsigned size){
    unsigned fact = factorial(size);
    for (unsigned i=0; i<fact; ++i){
        delete[] permutations[i];
    }
    delete[] permutations;
}

// To calculate factorial
static unsigned factorial (unsigned i){
    unsigned fact = 1;
    for (i; i>1; --i) fact *= i;
    return fact;
}

/*------------------------- Common Functions ---------------------------------*/

TEST(CommonFunctionsTest, copyArray_test){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    int testArray[size] = 
        // Test Case
        // Expected Result
        {5, 4, 3, 2, 1};
    int resultArray[size];
    /*-Perform Test---------------------------------------*/
    copyArray(testArray, resultArray, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(testArray[i], resultArray[i]);
}

TEST(CommonFunctionsTest, factorial_test){
    /*-Test Setup-----------------------------------------*/
    const unsigned test_case = 5;
    const unsigned expected = 120;
    unsigned result;
    /*-Perform Test---------------------------------------*/
    result = factorial(test_case);
    /*-Check Results--------------------------------------*/
    ASSERT_EQ(expected, result);
}

TEST(CommonFunctionsTest, permuteArray_test){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 3;
    const unsigned sizeFact = 3*2*1;
    int testArray[size] = 
        // Test Case
        {1, 2, 3};
    const int expectedPermutations[sizeFact][size] =
        // Expected Results
        {
            {1, 2, 3},
            {1, 3, 2},
            {2, 1, 3},
            {2, 3, 1},
            {3, 2, 1},
            {3, 1, 2}
        };
    int** resultPermutations;
    /*-Perform Test---------------------------------------*/
    resultPermutations = permuteArray(testArray, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        for(unsigned j=0; j<size; ++j)
            ASSERT_EQ(expectedPermutations[i][j],
                resultPermutations[i][j]);
    /*-Clean Up-------------------------------------------*/
    freePermuteArray(resultPermutations, size);
}
/*--------------------------- Quick Sort -------------------------------------*/

TEST(QuickSortTest, OneElementArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 1;
    int unsorted[size] = 
        // Test Case (ie. unsorted array)
        {1};
    const int sort_expected[size] = 
        // Expected Result
        {1};
    int sort_result[size];
    copyArray(unsorted, sort_result, size);
    /*-Perform Test---------------------------------------*/
    quickSort(sort_result, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}

TEST(QuickSortTest, TwoElementArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 2;
    int unsorted[size] = 
        // Test Case (ie. unsorted array)
        {50, 10};
    const int sort_expected[size] = 
        // Expected Result
        {10, 50};
    int sort_result[size];
    copyArray(unsorted, sort_result, size);
    /*-Perform Test---------------------------------------*/
    quickSort(sort_result, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}

TEST(QuickSortTest, FullReversedArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    int unsorted[size] = 
        // Test Case (ie. unsorted array)
        {50, 10, 6, 3, 2};
    const int sort_expected[size] = 
        // Expected Result
        {2, 3, 6, 10, 50};
    int sort_result[size];
    copyArray(unsorted, sort_result, size);
    /*-Perform Test---------------------------------------*/
    quickSort(sort_result, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}

TEST(QuickSortTest, FullReversedNegativeArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    int unsorted[size] = 
        // Test Case (ie. unsorted array)
        {-2, -3, -6, -10, -50};
    const int sort_expected[size] = 
        // Expected Result
        {-50, -10, -6, -3, -2};
    int sort_result[size];
    copyArray(unsorted, sort_result, size);
    /*-Perform Test---------------------------------------*/
    quickSort(sort_result, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}

TEST(QuickSortTest, FullReversedEvenSizeArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 4;
    int unsorted[size] = 
        // Test Case (ie. unsorted array)
        {50, 10, 6, 3};
    const int sort_expected[size] = 
        // Expected Result
        {3, 6, 10, 50};
    int sort_result[size];
    copyArray(unsorted, sort_result, size);
    /*-Perform Test---------------------------------------*/
    quickSort(sort_result, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}
 
TEST(QuickSortTest, SortedArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    int unsorted[size] = 
        // Test Case (ie. unsorted array)
        {2, 3, 6, 10, 50};
    const int sort_expected[size] = 
        // Expected Result
        {2, 3, 6, 10, 50};
    int sort_result[size];
    copyArray(unsorted, sort_result, size);
    /*-Perform Test---------------------------------------*/
    quickSort(sort_result, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}

TEST(QuickSortTest, AllSameElementsArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    int unsorted[size] = 
        // Test Case (ie. unsorted array)
        {1, 1, 1, 1, 1};
    const int sort_expected[size] = 
        // Expected Result
        {1, 1, 1, 1, 1};
    int sort_result[size];
    copyArray(unsorted, sort_result, size);
    /*-Perform Test---------------------------------------*/
    quickSort(sort_result, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}

TEST(QuickSortTest, AllPermutationsOfSortedArrayOddSize){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    const unsigned sizeFact = 5*4*3*2*1;
    int unsorted[size] = 
        // Test Case Base
        {1, 2, 3, 4, 5};
    const int sort_expected[size] = 
        // Expected Result
        {1, 2, 3, 4, 5};
    int** sort_results;
    sort_results = permuteArray(unsorted, size);
    /*-Perform Test---------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        quickSort(sort_results[i], size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        for(unsigned j=0; j<size; ++j)
            ASSERT_EQ(sort_expected[j],
                sort_results[i][j]);
    /*-Clean Up-------------------------------------------*/
    freePermuteArray(sort_results, size);
}

TEST(QuickSortTest, AllPermutationsOfSortedArrayEvenSize){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 4;
    const unsigned sizeFact = 4*3*2*1;
    int unsorted[size] = 
        // Test Case Base
        {1, 2, 3, 4};
    const int sort_expected[size] = 
        // Expected Result
        {1, 2, 3, 4};
    int** sort_results;
    sort_results = permuteArray(unsorted, size);
    /*-Perform Test---------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        quickSort(sort_results[i], size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        for(unsigned j=0; j<size; ++j)
            ASSERT_EQ(sort_expected[j],
                sort_results[i][j]);
    /*-Clean Up-------------------------------------------*/
    freePermuteArray(sort_results, size);
}

TEST(QuickSortTest, AllPermutationsOfSortedNegativeArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    const unsigned sizeFact = 5*4*3*2*1;
    int unsorted[size] = 
        // Test Case Base
        {-5, -4, -3, -2, -1};
    const int sort_expected[size] = 
        // Expected Result
        {-5, -4, -3, -2, -1};
    int** sort_results;
    sort_results = permuteArray(unsorted, size);
    /*-Perform Test---------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        quickSort(sort_results[i], size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        for(unsigned j=0; j<size; ++j)
            ASSERT_EQ(sort_expected[j],
                sort_results[i][j]);
    /*-Clean Up-------------------------------------------*/
    freePermuteArray(sort_results, size);
}

TEST(QuickSortTest, AllPermutationsOfArrayWithRepeats){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 7;
    const unsigned sizeFact = 7*6*5*4*3*2*1;
    int unsorted[size] = 
        // Test Case Base
        {1, 2, 3, 2, 2, 1, -5};
    const int sort_expected[size] = 
        // Expected Result
        {-5, 1, 1, 2, 2, 2, 3};
    int** sort_results;
    sort_results = permuteArray(unsorted, size);
    /*-Perform Test---------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        quickSort(sort_results[i], size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        for(unsigned j=0; j<size; ++j)
            ASSERT_EQ(sort_expected[j],
                sort_results[i][j]);
    /*-Clean Up-------------------------------------------*/
    freePermuteArray(sort_results, size);
}

/*------------------------------ Merge Sort ----------------------------------*/

TEST(MergeSortTest, OneElementArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 1;
    int unsorted[size] = 
        // Test Case (ie. unsorted array)
        {1};
    const int sort_expected[size] = 
        // Expected Result
        {1};
    int sort_result[size];
    copyArray(unsorted, sort_result, size);
    /*-Perform Test---------------------------------------*/
    mergSort(sort_result, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}

TEST(MergeSortTest, TwoElementArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 2;
    int unsorted[size] = 
        // Test Case (ie. unsorted array)
        {50, 10};
    const int sort_expected[size] = 
        // Expected Result
        {10, 50};
    int sort_result[size];
    copyArray(unsorted, sort_result, size);
    /*-Perform Test---------------------------------------*/
    mergSort(sort_result, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}

TEST(MergeSortTest, FullReversedArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    int unsorted[size] = 
        // Test Case (ie. unsorted array)
        {50, 10, 6, 3, 2};
    const int sort_expected[size] = 
        // Expected Result
        {2, 3, 6, 10, 50};
    int sort_result[size];
    copyArray(unsorted, sort_result, size);
    /*-Perform Test---------------------------------------*/
    mergSort(sort_result, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}

TEST(MergeSortTest, FullReversedNegativeArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    int unsorted[size] = 
        // Test Case (ie. unsorted array)
        {-2, -3, -6, -10, -50};
    const int sort_expected[size] = 
        // Expected Result
        {-50, -10, -6, -3, -2};
    int sort_result[size];
    copyArray(unsorted, sort_result, size);
    /*-Perform Test---------------------------------------*/
    mergSort(sort_result, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}

TEST(MergeSortTest, FullReversedEvenSizeArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 4;
    int unsorted[size] = 
        // Test Case (ie. unsorted array)
        {50, 10, 6, 3};
    const int sort_expected[size] = 
        // Expected Result
        {3, 6, 10, 50};
    int sort_result[size];
    copyArray(unsorted, sort_result, size);
    /*-Perform Test---------------------------------------*/
    mergSort(sort_result, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}
 
TEST(MergeSortTest, SortedArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    int unsorted[size] = 
        // Test Case (ie. unsorted array)
        {2, 3, 6, 10, 50};
    const int sort_expected[size] = 
        // Expected Result
        {2, 3, 6, 10, 50};
    int sort_result[size];
    copyArray(unsorted, sort_result, size);
    /*-Perform Test---------------------------------------*/
    mergSort(sort_result, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}

TEST(MergeSortTest, AllSameElementsArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    int unsorted[size] = 
        // Test Case (ie. unsorted array)
        {1, 1, 1, 1, 1};
    const int sort_expected[size] = 
        // Expected Result
        {1, 1, 1, 1, 1};
    int sort_result[size];
    copyArray(unsorted, sort_result, size);
    /*-Perform Test---------------------------------------*/
    mergSort(sort_result, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}

TEST(MergeSortTest, AllPermutationsOfSortedArrayOddSize){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    const unsigned sizeFact = 5*4*3*2*1;
    int unsorted[size] = 
        // Test Case Base
        {1, 2, 3, 4, 5};
    const int sort_expected[size] = 
        // Expected Result
        {1, 2, 3, 4, 5};
    int** sort_results;
    sort_results = permuteArray(unsorted, size);
    /*-Perform Test---------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        mergSort(sort_results[i], size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        for(unsigned j=0; j<size; ++j)
            ASSERT_EQ(sort_expected[j],
                sort_results[i][j]);
    /*-Clean Up-------------------------------------------*/
    freePermuteArray(sort_results, size);
}

TEST(MergeSortTest, AllPermutationsOfSortedArrayEvenSize){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 4;
    const unsigned sizeFact = 4*3*2*1;
    int unsorted[size] = 
        // Test Case Base
        {1, 2, 3, 4};
    const int sort_expected[size] = 
        // Expected Result
        {1, 2, 3, 4};
    int** sort_results;
    sort_results = permuteArray(unsorted, size);
    /*-Perform Test---------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        mergSort(sort_results[i], size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        for(unsigned j=0; j<size; ++j)
            ASSERT_EQ(sort_expected[j],
                sort_results[i][j]);
    /*-Clean Up-------------------------------------------*/
    freePermuteArray(sort_results, size);
}

TEST(MergeSortTest, AllPermutationsOfSortedNegativeArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    const unsigned sizeFact = 5*4*3*2*1;
    int unsorted[size] = 
        // Test Case Base
        {-5, -4, -3, -2, -1};
    const int sort_expected[size] = 
        // Expected Result
        {-5, -4, -3, -2, -1};
    int** sort_results;
    sort_results = permuteArray(unsorted, size);
    /*-Perform Test---------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        mergSort(sort_results[i], size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        for(unsigned j=0; j<size; ++j)
            ASSERT_EQ(sort_expected[j],
                sort_results[i][j]);
    /*-Clean Up-------------------------------------------*/
    freePermuteArray(sort_results, size);
}

TEST(MergeSortTest, AllPermutationsOfArrayWithRepeats){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 7;
    const unsigned sizeFact = 7*6*5*4*3*2*1;
    int unsorted[size] = 
        // Test Case Base
        {1, 2, 3, 2, 2, 1, -5};
    const int sort_expected[size] = 
        // Expected Result
        {-5, 1, 1, 2, 2, 2, 3};
    int** sort_results;
    sort_results = permuteArray(unsorted, size);
    /*-Perform Test---------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        mergSort(sort_results[i], size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        for(unsigned j=0; j<size; ++j)
            ASSERT_EQ(sort_expected[j],
                sort_results[i][j]);
    /*-Clean Up-------------------------------------------*/
    freePermuteArray(sort_results, size);
}

/*------------------------------ Heap Sort -----------------------------------*/

TEST(HeapSortTest, OneElementArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 1;
    int unsorted[size] = 
        // Test Case (ie. unsorted array)
        {1};
    const int sort_expected[size] = 
        // Expected Result
        {1};
    int sort_result[size];
    copyArray(unsorted, sort_result, size);
    /*-Perform Test---------------------------------------*/
    heapSort(sort_result, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}

TEST(HeapSortTest, TwoElementArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 2;
    int unsorted[size] = 
        // Test Case (ie. unsorted array)
        {50, 10};
    const int sort_expected[size] = 
        // Expected Result
        {10, 50};
    int sort_result[size];
    copyArray(unsorted, sort_result, size);
    /*-Perform Test---------------------------------------*/
    heapSort(sort_result, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}

TEST(HeapSortTest, FullReversedArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    int unsorted[size] = 
        // Test Case (ie. unsorted array)
        {50, 10, 6, 3, 2};
    const int sort_expected[size] = 
        // Expected Result
        {2, 3, 6, 10, 50};
    int sort_result[size];
    copyArray(unsorted, sort_result, size);
    /*-Perform Test---------------------------------------*/
    heapSort(sort_result, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}

TEST(HeapSortTest, FullReversedNegativeArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    int unsorted[size] = 
        // Test Case (ie. unsorted array)
        {-2, -3, -6, -10, -50};
    const int sort_expected[size] = 
        // Expected Result
        {-50, -10, -6, -3, -2};
    int sort_result[size];
    copyArray(unsorted, sort_result, size);
    /*-Perform Test---------------------------------------*/
    heapSort(sort_result, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}

TEST(HeapSortTest, FullReversedEvenSizeArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 4;
    int unsorted[size] = 
        // Test Case (ie. unsorted array)
        {50, 10, 6, 3};
    const int sort_expected[size] = 
        // Expected Result
        {3, 6, 10, 50};
    int sort_result[size];
    copyArray(unsorted, sort_result, size);
    /*-Perform Test---------------------------------------*/
    heapSort(sort_result, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}
 
TEST(HeapSortTest, SortedArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    int unsorted[size] = 
        // Test Case (ie. unsorted array)
        {2, 3, 6, 10, 50};
    const int sort_expected[size] = 
        // Expected Result
        {2, 3, 6, 10, 50};
    int sort_result[size];
    copyArray(unsorted, sort_result, size);
    /*-Perform Test---------------------------------------*/
    heapSort(sort_result, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}

TEST(HeapSortTest, AllSameElementsArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    int unsorted[size] = 
        // Test Case (ie. unsorted array)
        {1, 1, 1, 1, 1};
    const int sort_expected[size] = 
        // Expected Result
        {1, 1, 1, 1, 1};
    int sort_result[size];
    copyArray(unsorted, sort_result, size);
    /*-Perform Test---------------------------------------*/
    heapSort(sort_result, size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}

TEST(HeapSortTest, AllPermutationsOfSortedArrayOddSize){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    const unsigned sizeFact = 5*4*3*2*1;
    int unsorted[size] = 
        // Test Case Base
        {1, 2, 3, 4, 5};
    const int sort_expected[size] = 
        // Expected Result
        {1, 2, 3, 4, 5};
    int** sort_results;
    sort_results = permuteArray(unsorted, size);
    /*-Perform Test---------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        heapSort(sort_results[i], size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        for(unsigned j=0; j<size; ++j)
            ASSERT_EQ(sort_expected[j],
                sort_results[i][j]);
    /*-Clean Up-------------------------------------------*/
    freePermuteArray(sort_results, size);
}

TEST(HeapSortTest, AllPermutationsOfSortedArrayEvenSize){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 4;
    const unsigned sizeFact = 4*3*2*1;
    int unsorted[size] = 
        // Test Case Base
        {1, 2, 3, 4};
    const int sort_expected[size] = 
        // Expected Result
        {1, 2, 3, 4};
    int** sort_results;
    sort_results = permuteArray(unsorted, size);
    /*-Perform Test---------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        heapSort(sort_results[i], size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        for(unsigned j=0; j<size; ++j)
            ASSERT_EQ(sort_expected[j],
                sort_results[i][j]);
    /*-Clean Up-------------------------------------------*/
    freePermuteArray(sort_results, size);
}

TEST(HeapSortTest, AllPermutationsOfSortedNegativeArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 5;
    const unsigned sizeFact = 5*4*3*2*1;
    int unsorted[size] = 
        // Test Case Base
        {-5, -4, -3, -2, -1};
    const int sort_expected[size] = 
        // Expected Result
        {-5, -4, -3, -2, -1};
    int** sort_results;
    sort_results = permuteArray(unsorted, size);
    /*-Perform Test---------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        heapSort(sort_results[i], size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        for(unsigned j=0; j<size; ++j)
            ASSERT_EQ(sort_expected[j],
                sort_results[i][j]);
    /*-Clean Up-------------------------------------------*/
    freePermuteArray(sort_results, size);
}

TEST(HeapSortTest, AllPermutationsOfArrayWithRepeats){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 7;
    const unsigned sizeFact = 7*6*5*4*3*2*1;
    int unsorted[size] = 
        // Test Case Base
        {1, 2, 3, 2, 2, 1, -5};
    const int sort_expected[size] = 
        // Expected Result
        {-5, 1, 1, 2, 2, 2, 3};
    int** sort_results;
    sort_results = permuteArray(unsorted, size);
    /*-Perform Test---------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        heapSort(sort_results[i], size);
    /*-Check Results--------------------------------------*/
    for (unsigned i=0; i<sizeFact; ++i)
        for(unsigned j=0; j<size; ++j)
            ASSERT_EQ(sort_expected[j],
                sort_results[i][j]);
    /*-Clean Up-------------------------------------------*/
    freePermuteArray(sort_results, size);
}

/*-------------------------------- MAIN --------------------------------------*/

int main (int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/*--------------------------------- END --------------------------------------*/
