#include <iostream>
#include <vector>
#include <cmath>

#include "bozosort.hpp"
typedef std::vector<int> vector_t;
typedef std::vector<std::vector<int>> matrix_t;

//using namespace BozoSort;

void print_vector(vector_t array)
{
    std::cout << '[';
    for (int i = 0; i < array.size()-1; ++i)
    {
        std::cout << array[i] << ", ";
    }
    std::cout << array[array.size()-1] << ']' << std::endl;
}

void print_matrix(matrix_t array)
{
    std::cout << '[' << std::endl;
    for (vector_t row : array)
    {
        std::cout << '\t';
        print_vector(row);
    }
    std::cout << ']' << std::endl;
}

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

    

    print_vector(vector);
    print_matrix(matrix);

    print_vector(BozoSort(vector, true));
    print_vector(BozoSort(vector, false));
    print_vector(BozoSort(matrix, true));
    print_vector(BozoSort(matrix, false));
    print_vector(BozoSort(vector[0], vector[1], vector[2], true));
    print_vector(BozoSort(vector[0], vector[1], vector[2], false));
}