#include <iostream>
#include "Profiler.h"

Profiler profiler("AVG");

int largestIdx(int n1, int n2, int n3, int *arr, int size, int *opCount)
{
    if (n2 < size && arr[n2] > arr[n1])
    {
        opCount++;
        n1 = n2;
    }
    if (n3 < size && arr[n3] > arr[n1])
    {
        opCount++;
        n1 = n3;
    }
    opCount += 2;
    return n1;
}

void Heapify(int *arr, int i, int size, Operation op)
{
    int opCount = 0;
    int largest = largestIdx(i, (2 * i) + 1, (2 * i) + 2, arr, size, &opCount);
    op.count(opCount);

    if (largest != i)
    {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        op.count(3);
        Heapify(arr, largest, size, op);
    }
}

void Build_Heap_BottomUp(int *arr, int size)
{
    Operation op = profiler.createOperation("BU_op", size);
    for (int i = (size / 2) - 1; i > -1; i--)
    {
        Heapify(arr, i, size, op);
    }
}

int parent(int i)
{
    return (i - 1) / 2;
}

void HeapifyTD(int *arr, int i, Operation opTD)
{
    int idx = parent(i);
    if (idx >= 0)
    {
        opTD.count();
        if (arr[i] > arr[idx])
        {
            opTD.count(3);
            int temp = arr[idx];
            arr[idx] = arr[i];
            arr[i] = temp;
            HeapifyTD(arr, idx, opTD);
        }
    }
}

void Build_Heap_TopDown(int *arr, int size)
{
    Operation opTD = profiler.createOperation("TD_op", size);
    for (int i = 1; i < size; i++)
    {
        HeapifyTD(arr, i, opTD);
    }
}

void doTheThing(int ComplexityCase)
{
    const int MAX_S = 10000;
    const int STEP = 100;

    int array[MAX_S], copy_array[MAX_S];
    int nrTests = 1;
    if (ComplexityCase == 0)
    {
        nrTests = 5;
    }

    for (int j = 0; j < nrTests; j++)
    {
        for (int i = STEP; i < MAX_S; i += STEP)
        {
            printf("%d\n", i);
            if (ComplexityCase == 0)
            { // AVG case
                FillRandomArray(array, i, 100, 10000, false, 0);
                CopyArray(copy_array, array, i);

                Build_Heap_BottomUp(array, i);
                Build_Heap_TopDown(copy_array, i);
            }
            else
            { // Worst case
                FillRandomArray(array, i, 100, 10000, false, 1);
                CopyArray(copy_array, array, i);

                Build_Heap_BottomUp(array, i);
                Build_Heap_TopDown(copy_array, i);
            }
        }
    }
    profiler.divideValues("BU_op", nrTests);
    profiler.divideValues("TD_op", nrTests);

    profiler.createGroup("HeapBuild", "TD_op", "BU_op");
}
void Heapsort(int *arr, int size)
{
    Operation X = profiler.createOperation("X", size);
    Build_Heap_BottomUp(arr, size);
    for (int i = size - 1; i > -1; i--)
    {
        int temp = arr[i];
        arr[i] = arr[0];
        arr[0] = temp;
        Heapify(arr, 0, i, X);
    }
}

void print(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d, ", arr[i]);
    printf("\n");
}
void demo_HeapSort()
{
    int arr[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    print(arr, size);

    Heapsort(arr, size);

    print(arr, size);
}
void demo_BuildBT()
{
    int arr[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int size = sizeof(arr) / sizeof(arr[0]);
    print(arr, size);

    Build_Heap_BottomUp(arr, size);

    print(arr, size);
}

void demo_BuildTD()
{
    int arr[] = {2, 9, 7, 6, 5, 8, 10, 3, 6, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    print(arr, size);

    Build_Heap_TopDown(arr, size);

    print(arr, size);
}

int main()
{
    //  demo_HeapSort();
    //  printf("\n");
    //  demo_BuildBT();
    //  printf("\n");
    //  demo_BuildTD();

    doTheThing(0);
    profiler.reset("Worst");
    doTheThing(2);
    profiler.showReport();

    return 0;
}