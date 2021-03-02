#include <cstdio> // понты

int *create(int len, int start, int inc)
{
    if (len < 0)
    {
        fprintf(stderr, "Cannot create arr with length %d.\n", len);
        return nullptr;
    }
    int *arr = new int[len];
    if (!arr)
    {
        fprintf(stderr, "Could not create array with length %d.\n", len);
        return nullptr;
    }
    for (int i = 0; i < len; ++i)
    {
        arr[i] = start;
        start += inc;
    }
    return arr;
}

int *sort(int *arr, int len)
{
    if (len < 0)
    {
        fprintf(stderr, "Cannot sort array with length %d.\n", len);
        return arr;
    }
    if (!arr)
    {
        fprintf(stderr, "Cannot sort nullptr array.\n");
        return arr;
    }
    for (int i = 1; i < len; ++i)
    {
        for (int j = i; j > 0; --j)
        {
            if (arr[j] < arr[j-1])
            {
                int temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
        }
    }
    return arr;
}

int *print(int *arr, int len)
{
    if (len < 0)
    {
        fprintf(stderr, "Cannot print array with length %d.\n", len);
        return arr;
    }
    if (!arr)
    {
        fprintf(stderr, "Cannot print nullptr array.\n");
        return arr;
    }
    if (len == 0)
    {
        printf("[]\n");
        return arr;
    }
    printf("[%d", *arr);
    for (int i = 1; i < len; ++i)
        printf(", %d", arr[i]);
    printf("]\n");
    return arr;
}

int main(int argc, char* argv[], char* envp[])
{
    int len, start, inc;
    puts("Enter length, begin value and increment.\n");
    scanf("%d%d%d", &len, &start, &inc);
    int *arr = create(len, start, inc);
    sort(arr, len);
    print(arr, len);
    return 0;
}
