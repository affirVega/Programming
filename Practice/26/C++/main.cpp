#include <iostream>
#include <vector>
#include <cmath>

#include "bozosort.hpp"
template<class T>
using vector_t = std::vector<T>;
template<class T>
using matrix_t = std::vector<std::vector<T>>;

//using namespace BozoSort;

template<class T>
void print_vector(
    vector_t<T> vector,
    const char * start = "",
    const char * delim = " ",
    const char * end = "\n");

template<class T>
void print_matrix(
    matrix_t<T> matrix,
    const char * start = "",
    const char * delim = " ",
    const char * end = "\n");

template<class T>
std::pair<vector_t<T>, matrix_t<T>> get_T_vec_and_matrix()
{
    int n;
    std::cin >> n;
    matrix_t<T> matrix;
    vector_t<T> vector;
    vector_t<T> buffer;
    for (int i = 1; i <= n; ++i)
    {
        T elem;
        std::cin >> elem;
        buffer.push_back(elem);
        vector.push_back(elem);
        if (i % int(std::sqrt(n)) == 0)
        {
            matrix.push_back(buffer);
            buffer.clear();
        }
    }
    return {vector, matrix};
}

int main()
{
    auto floats = get_T_vec_and_matrix<float>();
    auto strings = get_T_vec_and_matrix<std::string>();

    vector_t<float> fvector = floats.first;
    matrix_t<float> fmatrix = floats.second;
    vector_t<std::string> svector = strings.first;
    matrix_t<std::string> smatrix = strings.second;

    print_vector(BozoSort::BozoSort(fvector, true));
    print_vector(BozoSort::BozoSort(fvector, false));
    print_vector(BozoSort::BozoSort(fmatrix, true)); 
    print_vector(BozoSort::BozoSort(fmatrix, false));
    print_vector(BozoSort::BozoSort(fvector[0], fvector[1], fvector[2], true));
    print_vector(BozoSort::BozoSort(fvector[0], fvector[1], fvector[2], false));

    print_vector(BozoSort::BozoSort(svector, true));
    print_vector(BozoSort::BozoSort(svector, false));
    print_vector(BozoSort::BozoSort(smatrix, true)); 
    print_vector(BozoSort::BozoSort(smatrix, false));
    print_vector(BozoSort::BozoSort(svector[0], svector[1], svector[2], true));
    print_vector(BozoSort::BozoSort(svector[0], svector[1], svector[2], false));
}

template<class T>
void print_vector(
    vector_t<T> vector,
    const char * start,
    const char * delim,
    const char * end)
{
    std::cout << start;
    for (int i = 0; i < vector.size()-1; ++i)
    {
        std::cout << vector[i] << delim;
    }
    std::cout << vector[vector.size()-1] << end << std::flush;
}

template<class T>
void print_matrix(
    matrix_t<T> matrix,
    const char * start,
    const char * delim,
    const char * end)
{
    std::cout << start << '\n';

    for (vector_t<T> row : matrix)
    {
        std::cout << '\t';
        print_vector(row, start, delim, end);
        std::cout << '\n';
    }

    std::cout << end << std::flush;
}