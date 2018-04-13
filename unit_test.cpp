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

static void copyArray(int array[], int newArray[], unsigned index){
    for (index; index>0; --index)
        newArray[index-1] = array[index-1];
}

static void printArray(int array[], unsigned size){
    std::cout << "[";
    for (unsigned i=0; i<size; ++i){
        std::cout << array[i];
        if (i != (size-1)) std::cout << ", ";
    }
    std::cout << "]\n";
}

static void swap(int array[], unsigned a, unsigned b){
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

static void permuteHelper(int array[], int* permutations[],
    unsigned* p_permuteIndex, unsigned at, unsigned size){
    if (at == (size-1)){
        copyArray(array, permutations[*p_permuteIndex], size);
        ++(*p_permuteIndex);
        return;
    }
    for (unsigned i=(at+1); i<size; ++i){
        swap(array, at, i);
        permuteHelper(array, permutations, p_permuteIndex, (at+1), size);
        swap(array, at, i);
    }
}

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

static void freePermuteArray(int** permutations, unsigned size){
    unsigned fact = factorial(size);
    for (unsigned i=0; i<fact; ++i){
        delete[] permutations[i];
    }
    delete[] permutations;
}

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
        // Test case
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
    // We left off here...
}
/*--------------------------- Quick Sort -------------------------------------*/

TEST(QuickSortTest, OneElementArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 1;
    int unsorted[size] = 
        // Test case (ie. unsorted array)
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
        // Test case (ie. unsorted array)
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
        // Test case (ie. unsorted array)
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
        // Test case (ie. unsorted array)
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
        // Test case (ie. unsorted array)
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
        // Test case (ie. unsorted array)
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
        // Test case (ie. unsorted array)
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

/*------------------------------ Merge Sort ----------------------------------*/

TEST(MergeSortTest, OneElementArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 1;
    int unsorted[size] = 
        // Test case (ie. unsorted array)
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
        // Test case (ie. unsorted array)
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
        // Test case (ie. unsorted array)
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
        // Test case (ie. unsorted array)
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
        // Test case (ie. unsorted array)
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
        // Test case (ie. unsorted array)
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
        // Test case (ie. unsorted array)
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

/*------------------------------ Heap Sort -----------------------------------*/

TEST(HeapSortTest, OneElementArray){
    /*-Test Setup-----------------------------------------*/
    const unsigned size = 1;
    int unsorted[size] = 
        // Test case (ie. unsorted array)
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
        // Test case (ie. unsorted array)
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
        // Test case (ie. unsorted array)
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
        // Test case (ie. unsorted array)
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
        // Test case (ie. unsorted array)
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
        // Test case (ie. unsorted array)
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
        // Test case (ie. unsorted array)
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

/*-------------------------------- MAIN --------------------------------------*/

int main (int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/*--------------------------------- END --------------------------------------*/
