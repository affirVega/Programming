#pragma once
#include <cstdlib>
#include <ctime>
#include <vector>

namespace BozoSort {
    typedef std::vector<int> vector_t;
    typedef std::vector<std::vector<int>> matrix_t;
    
    bool     IsSorted(const vector_t &vector, bool ascending = true);
    vector_t BozoSort(const vector_t &vector, bool ascending = true);
    vector_t BozoSort(const matrix_t &matrix, bool ascending = true);
    vector_t BozoSort(int a, int b, int c,   bool ascending = true);
    
    //-----------------------------------

    //    Defenitions

    //-----------------------------------
    
    bool IsSorted(const vector_t &vector, bool ascending)
    {
        size_t size = vector.size();
        
        if (ascending)
        {
            for (int i = 1; i < size; ++i)
            {
                if (vector[i-1] > vector[i])
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
                if (vector[i-1] < vector[i])
                {
                    return false;
                }
            }
            return true;
        }
    }

    vector_t BozoSort(const vector_t &vector, bool ascending)
    {
        std::srand(std::time(0));

        vector_t result = vector;
        if (vector.size() < 2)
        {
            return result;
        }

        size_t size = result.size();
        while(! IsSorted(result, ascending))
        {
            int a = std::rand() % size;
            int b = std::rand() % size;
            std::swap(result[a], result[b]);
        }
        return result;
    }

    vector_t BozoSort(const matrix_t &matrix, bool ascending)
    {
        vector_t result;
        for (vector_t row : matrix)
        {
            for (int elem : row)
            {
                result.push_back(elem);
            }
        }
        return BozoSort(result, ascending);
    }

    vector_t BozoSort(int a, int b, int c, bool ascending)
    {
        vector_t result = {a, b, c};
        return BozoSort(result, ascending);
    }
}
