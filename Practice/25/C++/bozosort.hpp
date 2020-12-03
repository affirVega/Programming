#pragma once
#include <cstdlib>
#include <ctime>
#include <vector>

//namespace BozoSort {
    
    typedef std::vector<int> vector_t;
    typedef std::vector<std::vector<int>> matrix_t;
    /*
    bool     IsSorted(vector_t array, bool ascending);
    vector_t BozoSort(vector_t array, bool ascending);
    vector_t BozoSort(matrix_t array, bool ascending);
    vector_t BozoSort(int a, int b, int c, bool ascending);
    */
    bool IsSorted(vector_t &array, bool ascending = true)
    {
        size_t size = array.size();
        
        if (ascending)
        {
            for (int i = 1; i < size; ++i)
            {
                if (array[i-1] > array[i])
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            for (int i = 1; i < size; ++i)
            {
                if (array[i-1] < array[i])
                {
                    return false;
                }
            }
            return true;
        }
    }

    vector_t BozoSort(vector_t &array, bool ascending = true)
    {
        std::srand(std::time(0));

        vector_t result;
        if (array.size() < 2)
        {
            return result;
        }

        size_t size = array.size();

        while(! IsSorted(result, ascending))
        {
            int a = std::rand() % size;
            int b = std::rand() % size;
            
            std::swap(array[a], array[b]);
        }
        return result;
    }

    vector_t BozoSort(matrix_t &array, bool ascending = true)
    {
        vector_t result;
        for (vector_t row : array)
        {
            for (int elem : row)
            {
                result.push_back(elem);
            }
        }
        return BozoSort(result, ascending);
    }

    vector_t BozoSort(int a, int b, int c, bool ascending = true)
    {
        vector_t result = {a, b, c};
        return BozoSort(result);
    }

//}
