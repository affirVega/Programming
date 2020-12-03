#include <iostream>
#include <vector>
#include <cmath>

#include "bozosort.hpp"
typedef std::vector<int> vector_t;
typedef std::vector<std::vector<int>> matrix_t;

//using namespace BozoSort;

void print_vector(
    vector_t vector,
    const char * start = "",
    const char * delim = " ",
    const char * end = "\n");

void print_matrix(
    matrix_t matrix,
    const char * start = "",
    const char * delim = " ",
    const char * end = "\n");

int main()
{
    int n;
    std::cin >> n;
    matrix_t matrix;
    vector_t vector;
    vector_t buffer;
    for (int i = 1; i <= n; ++i)
    {
        int num;
        std::cin >> num;
        buffer.push_back(num);
        vector.push_back(num);
        if (i % int(std::sqrt(n)) == 0)
        {
            matrix.push_back(buffer);
            buffer.clear();
        }
    }

    print_vector(BozoSort::BozoSort(vector, true));
    print_vector(BozoSort::BozoSort(vector, false));
    print_vector(BozoSort::BozoSort(matrix, true)); 
    print_vector(BozoSort::BozoSort(matrix, false));
    print_vector(BozoSort::BozoSort(vector[0], vector[1], vector[2], true));
    print_vector(BozoSort::BozoSort(vector[0], vector[1], vector[2], false));
}

void print_vector(
    vector_t vector,
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

void print_matrix(
    matrix_t matrix,
    const char * start,
    const char * delim,
    const char * end)
{
    std::cout << start << '\n';

    for (vector_t row : matrix)
    {
        std::cout << '\t';
        print_vector(row, start, delim, end);
        std::cout << '\n';
    }

    std::cout << end << std::flush;
}