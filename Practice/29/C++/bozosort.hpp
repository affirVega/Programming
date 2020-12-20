#pragma once
#include <cstdlib>
#include <ctime>
#include <vector>

namespace BozoSort {
template<class T>
using vector_t = std::vector<T>;

template<class T>
using matrix_t = std::vector<std::vector<T>>;

template<class T>
bool     IsSorted(const vector_t<T> &vector, bool ascending = true);
template<class T>
vector_t<T> BozoSort(const vector_t<T> &vector, bool ascending = true);
template<class T>
vector_t<T> BozoSort(const matrix_t<T> &matrix, bool ascending = true);
template<class T>
vector_t<T> BozoSort(T a, T b, T c,   bool ascending = true);

//-----------------------------------

//    Defenitions

//-----------------------------------

template<class T>
bool IsSorted(const vector_t<T> &vector, bool ascending)
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

template<class T>
vector_t<T> BozoSort(const vector_t<T> &vector, bool ascending)
{
    std::srand(std::time(0));

    vector_t<T> result = vector;
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

template<class T>
vector_t<T> BozoSort(const matrix_t<T> &matrix, bool ascending)
{
    vector_t<T> result;
    for (auto row : matrix)
    {
        for (auto elem : row)
        {
            result.push_back(elem);
        }
    }
    return BozoSort(result, ascending);
}

template<class T>
vector_t<T> BozoSort(T a, T b, T c, bool ascending)
{
    vector_t<T> result = {a, b, c};
    return BozoSort(result, ascending);
}

}