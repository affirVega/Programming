#include <cstdio>
#include "IntArray.h"

int main(int argc, char *argv[])
{
    int size = 30;
    IntArray arr;

    create(arr, size);
    for (int i = 0; i < size; ++i)
        set(arr, i, i+1);
    print(arr);

    resize(arr, 50);
    print(arr);

    resize(arr, 10);
    print(arr);

    destroy(arr);
}

