#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include "IntArray.h"

void create(IntArray& arr, int size)
{
    if (size <= 0)
    {
        fprintf(stderr, "Cannot create arr with length %d.\n", size);
        return;
    }
    arr.data = new int[size];
    if (!arr.data)
    {
        fprintf(stderr, "Could not create array with length %d.\n", size);
        return;
    }
    arr.size = size;
}
void create(IntArray* arr, int size)
{
    create(*arr, size);
}

int get(IntArray& arr, int index)
{
    if (index < 0 || index >= arr.size)
    {
        fprintf(stderr, "Index out of range! Size %d, index %d.\n", arr.size, index);
        exit(1);
    }
    return arr.data[index];
}
int get(IntArray* arr, int index)
{
    return get(*arr, index);
}

void set(IntArray& arr, int index, int value)
{
    if (index < 0 || index >= arr.size)
    {
        fprintf(stderr, "Index out of range! Size %d, index %d.\n", arr.size, index);
        exit(1);
    }
    arr.data[index] = value;
}
void set(IntArray* arr, int index, int value)
{
    set(*arr, index, value);
}

void resize(IntArray& arr, int newSize)
{
    if (newSize <= 0)
    {
        return;
    }

    if (newSize == arr.size)
    {
        // do nothing
        return;
    }
    else if (newSize > arr.size)
    {
        // create new array and copy data
        int *newArray = new int[newSize];
        if (!newArray)
        {
            fprintf(stderr, "Could not create array with length %d.\n", newSize);
            return;
        }
        memcpy(newArray, arr.data, sizeof(int)*arr.size);

        // initialize rest of the memory with 0
        for (int i = arr.size; i < newSize; ++i)
            newArray[i] = 0;
        
        // delete old data with new array
        delete[] arr.data;
        arr.data = newArray;
        arr.size = newSize;
    }
    else // newSize < arr.size
    {
        // We don't just change the size because
        // the data that was cut off will be lost!
        // Will be no more information that cut off data is there.
        // That's a memory leak! That's why we create new array
        int *newArray = new int[newSize];
        if (!newArray)
        {
            fprintf(stderr, "Could not create array with length %d.\n", newSize);
            return;
        }
        memcpy(newArray, arr.data, sizeof(int)*newSize);

        // replace old array with new one
        delete[] arr.data;
        arr.data = newArray;
        arr.size = newSize;
    }
}
void resize(IntArray* arr, int newSize)
{
    resize(*arr, newSize);
}

void destroy(IntArray& arr)
{
    if (!arr.data)
    {
        delete[] arr.data;
        arr.data = nullptr;
    }
    arr.size = 0;
}
void destroy(IntArray* arr)
{
    destroy(*arr);
}

void print(IntArray& arr)
{
    if (arr.size == 0)
    {
        puts("[]");
        return;
    }
    if (arr.size < 0)
    {
        return;
    }
    printf("[%d", get(arr, 0));
    for (int i = 1; i < arr.size; ++i)
        printf(", %d", get(arr, i));
    printf("]\n");
}
void print(IntArray* arr)
{
    print(*arr);
}
