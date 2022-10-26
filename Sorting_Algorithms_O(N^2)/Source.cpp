#include <iostream>
#include "Profiler.h"

Profiler profiler("AVG");

void InsertionSort(int *array, int size) {
    Operation comparisons = profiler.createOperation("Icomp", size);
    Operation assignments = profiler.createOperation("Iassig", size);

    int j;
    for (int i = 1; i < size; i++) {
        int aux = array[i];                 assignments.count(); // A++
        j = i - 1;
        while (j > -1 && array[j] > aux) {  comparisons.count(); // C++

            array[j + 1] = array[j];        assignments.count(); // A++
            j--;
        }
        if (j < 0 || j == i - 1) {
            comparisons.count(); // C++
        }
        if (j + 1 != i) {
            array[j + 1] = aux;             assignments.count(); // A++
        }
    }
}
void SelectionSort(int *array, int size) {
    Operation comparisons = profiler.createOperation("Scomp", size);
    Operation assignments = profiler.createOperation("Sassig", size);

    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            comparisons.count(); // C++
            if (array[min_idx] > array[j]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {             
            assignments.count(3); // A+3
            int aux = array[min_idx];
            array[min_idx] = array[i];
            array[i] = aux;
        }
    }
}
void BubbleSort(int *array, int size) {
    Operation comparisons = profiler.createOperation("Bcomp", size);
    Operation assignments = profiler.createOperation("Bassig", size);

    bool swap; // For stopping condition
    for (int i = 0; i < size - 1; i++) {
           swap = false;
        for (int j = 0; j < size - i - 1; j++) {
            comparisons.count(); // C++
            if (array[j] > array[j + 1]) {
                assignments.count(3); // A+3
                int aux = array[j];
                array[j] = array[j + 1];
                array[j+1] = aux;
                swap = true;
            }
        }
        if(!swap) { // Stopping condition
            break;
        }
    }
}


int BinarySearch(int *array, int start, int end, int target, int *comp) { 
// return the right position in the array for target
    while(start < end) { 
    if(array[( start + end ) / 2] == target ) {         //comp++
        *comp = *comp + 1;
        return (( start + end ) / 2) + 1;

    }
    else if(array[( start + end ) / 2] < target) {     //comp++
        start = ((start + end) / 2) + 1;
    }
    else {
        end = (( start + end ) / 2);
    }
        *comp = *comp + 2;
    }
    return start;
}
void BinaryInsertionSort(int *array, int size ) {
    
Operation comparisons = profiler.createOperation("BinaryComp", size);
Operation assignments = profiler.createOperation("BinaryAssig", size);

    for(int i = 1; i < size; i++) {
        int comp = 0;   // nr of comparisons made in binary search
        int index = BinarySearch(array, 0, i, array[i], &comp);
        comparisons.count(comp); // C++
        if(i > index) {
            int aux = array[i];                 assignments.count(); // A++
            for(int j = i; j > index; j--) {
                array[j] = array[j - 1];        assignments.count(); // A++
            }
            array[index] = aux;                 assignments.count(); // A++
        }
    }  

}


void perform(int ComplexityCase) {
    const int MAX_S = 10000;
    const int STEP = 100;

    int array[MAX_S], copy_array[MAX_S];

    int nrTests = 1;
    if (ComplexityCase == 0) {
        nrTests = 5;
    }

    for (int j = 0; j < nrTests; j++) {
        for (int i = 100; i < MAX_S; i += STEP) {
            system("CLS");
            printf("%d/3: Loading %d/%d: %d%\n",ComplexityCase + 1, j, nrTests, i/100);
            if (ComplexityCase == 0) { // AVG case
                FillRandomArray(array, i, 100, 10000, false, 0);

                CopyArray(copy_array, array, i);
                InsertionSort(array, i);
                CopyArray(array, copy_array, i);
                SelectionSort(array, i);
                CopyArray(array, copy_array, i);
                BubbleSort(array, i);
                CopyArray(array, copy_array, i);
                BinaryInsertionSort(array, i);
            }
            else if (ComplexityCase == 1) { // Best case
                FillRandomArray(array, i, 100, 10000, false, 1);

                CopyArray(copy_array, array, i);
                InsertionSort(array, i);
                CopyArray(array, copy_array, i);
                SelectionSort(array, i);
                CopyArray(array, copy_array, i);
                BubbleSort(array, i);
                CopyArray(array, copy_array, i);
                BinaryInsertionSort(array, i);
            }
            else { // Worst case
                FillRandomArray(array, i, 100, 10000, false, 2);
                CopyArray(copy_array, array, i);
                InsertionSort(array, i);

                FillRandomArray(array, i, 100, 10000, false, 1);
                array[i - 1] = 0; // array is in asscending order and last element is minimum.
                SelectionSort(array, i);

                CopyArray(array, copy_array, i);
                BubbleSort(array, i);

                CopyArray(array, copy_array, i);
                BinaryInsertionSort(array, i);
            }
        }
    }
    profiler.divideValues("Icomp", nrTests);
    profiler.divideValues("Iassig", nrTests);
    profiler.addSeries("Iop", "Icomp", "Iassig");

    profiler.divideValues("Scomp", nrTests);
    profiler.divideValues("Sassig", nrTests);
    profiler.addSeries("Sop", "Scomp", "Sassig");

    profiler.divideValues("Bcomp", nrTests);
    profiler.divideValues("Bassig", nrTests);
    profiler.addSeries("Bop", "Bcomp", "Bassig");

    profiler.divideValues("BinaryComp", nrTests);
    profiler.divideValues("BinaryAssig", nrTests);
    profiler.addSeries("BinaryOp", "BinaryComp", "BinaryAssig");

    profiler.createGroup("Comparison", "Icomp", "Scomp", "Bcomp", "BinaryComp");
    profiler.createGroup("Assignment", "Iassig", "Sassig", "Bassig", "BinaryAssig");
    profiler.createGroup("Operation", "Iop", "Sop", "Bop", "BinaryOp");
}

void demo_InsertionSort() {                  // Test algorithm
    int array[25]; // random array
    FillRandomArray(array, 25, 1, 100, false, 0);
    int size = (sizeof(array) / sizeof(int)); // size of the array

    printf("Array before insertion sort: ");
    for (int i = 0; i < size; i++)
        printf("%3d, ", array[i]);
    printf("\n");

    InsertionSort(array, size);

    printf("Array after  insert sorting: ");
    for (int i = 0; i < size; i++)
        printf("%3d, ", array[i]);
    printf("\n");

    // profiler sorted check
    if (IsSorted(array, size))
        printf("Sorted!");
    else
        printf("Not sorted!");
}
void demo_SelectionSort() {                  // Test algorithm
    int array[25]; // random array
    FillRandomArray(array, 25, 1, 100, false, 0);
    int size = (sizeof(array) / sizeof(int)); // size of the array

    printf("Array before selection sort: ");
    for (int i = 0; i < size; i++)
        printf("%3d, ", array[i]);
    printf("\n");

    SelectionSort(array, size);

    printf("Array after  selection sorting: ");
    for (int i = 0; i < size; i++)
        printf("%3d, ", array[i]);
    printf("\n");

    // profiler sorted check
    if (IsSorted(array, size))
        printf("Sorted!");
    else
        printf("Not sorted!");
}
void demo_BubbleSort() {                     // Test algorithm
    int array[25]; // random array
    FillRandomArray(array, 25, 1, 100, false, 0);
    int size = (sizeof(array) / sizeof(int)); // size of the array

    printf("Array before bubble sort: ");
    for (int i = 0; i < size; i++)
        printf("%3d, ", array[i]);
    printf("\n");

    BubbleSort(array, size);

    printf("Array after  bubble sorting: ");
    for (int i = 0; i < size; i++)
        printf("%3d, ", array[i]);
    printf("\n");

    // profiler sorted check
    if (IsSorted(array, size))
        printf("Sorted!");
    else
        printf("Not sorted!");
}
void demo_BinaryInsertionSort() {                  // Test algorithm
    int array[25]; // random array
    FillRandomArray(array, 25, 1, 100, false, 0);
    int size = (sizeof(array) / sizeof(int)); // size of the array

    printf("Array before binary insertion sort: ");
    for (int i = 0; i < size; i++)
        printf("%3d, ", array[i]);
    printf("\n");

    BinaryInsertionSort(array, size);

    printf("Array after  binary insert sorting: ");
    for (int i = 0; i < size; i++)
        printf("%3d, ", array[i]);
    printf("\n");

    // profiler sorted check
    if (IsSorted(array, size))
        printf("Sorted!");
    else
        printf("Not sorted!");
}

int main()
{
    // demo_InsertionSort();
    // demo_SelectionSort();
    // demo_BubbleSort();
    // demo_BinaryInsertionSort();
    
       perform(0);
       profiler.reset("Best");
       perform(1);
       profiler.reset("Worst");
       perform(2);
       profiler.showReport();
   
    return 0;
}