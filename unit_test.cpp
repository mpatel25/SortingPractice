#include "sorting.h"
#include <gtest/gtest.h>
#include <iostream>

/*------------------------ Static Declarations -------------------------------*/

static void copyArray(int array[], int newArray[], unsigned index);
static void printArray(int array[], unsigned size);

/*------------------------- Common Functions ---------------------------------*/

static void copyArray(int array[], int newArray[], unsigned index){
    for (index; index>0; --index)
        newArray[index-1] = array[index-1];
}

static void printArray(int array[], unsigned size){
    std::cout << "[";
    for (int i=0; i<size; ++i){
        std::cout << array[i];
        if (i != (size-1)) std::cout << ", ";
    }
    std::cout << "]\n";
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
    for (int i=0; i<size; ++i)
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
    for (int i=0; i<size; ++i)
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
    for (int i=0; i<size; ++i)
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
    for (int i=0; i<size; ++i)
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
    for (int i=0; i<size; ++i)
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
    for (int i=0; i<size; ++i)
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
    for (int i=0; i<size; ++i)
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
    for (int i=0; i<size; ++i)
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
    for (int i=0; i<size; ++i)
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
    for (int i=0; i<size; ++i)
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
    for (int i=0; i<size; ++i)
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
    for (int i=0; i<size; ++i)
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
    for (int i=0; i<size; ++i)
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
    for (int i=0; i<size; ++i)
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
    for (int i=0; i<size; ++i)
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
    for (int i=0; i<size; ++i)
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
    for (int i=0; i<size; ++i)
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
    for (int i=0; i<size; ++i)
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
    for (int i=0; i<size; ++i)
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
    for (int i=0; i<size; ++i)
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
    for (int i=0; i<size; ++i)
        ASSERT_EQ(sort_expected[i], sort_result[i]);
}

/*-------------------------------- MAIN --------------------------------------*/

int main (int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

/*--------------------------------- END --------------------------------------*/
