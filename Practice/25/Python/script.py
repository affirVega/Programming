import random
import math
from typing import List

def IsSorted(array: list, ascending = True) -> bool:
    '''
    Checks if array is sorted ascending or descending.
    '''
    size = len(array)
    if ascending:
        for i in range(1, size):
            if array[i-1] > array[i]:
                return False
    else: # descending
        for i in range(1, size):
            if array[i-1] < array[i]:
                return False
    return True

def BozoSort(array: list, ascending = True) -> List[int]:
    '''
    Swaps 2 random picked numbers and returns list if its sorted.
    Not recommended to use with len(array) >= 10.
    '''
    result = []

    if len(array) <= 1:
        return result

    if type(array[0]) == list:
        for row in array:
            result += row
    else:
        result = array.copy()

    size = len(result)
    while not IsSorted(result, ascending):
        a, b = random.randint(0, size-1), random.randint(0, size-1)
        result[a], result[b] = result[b], result[a]

    return result

# Python dosn't allow overloading of a function
def BozoSortForThree(a: int, b: int, c: int, ascending = True) -> List[int]:
    return BozoSort([a, b, c], ascending)

#------------------------------------------------------------------------------

#   Main function

#------------------------------------------------------------------------------

n = int(input('Введите целое число, являющееся квадратом целого числа: '))
n_sqrt = int(n**0.5)

print('Введите значения массива через пробел: ', end='')
vector = list(map(int, input().split(' ')))
matrix = []
row = []
i = 0
for elem in vector:
    row.append(elem)
    i += 1
    if (i % n_sqrt == 0):
        matrix.append(row)
        row = []
        i = 0
del row, i

'''
vector = []
for row in matrix:
    vector += row
'''

print(' '.join(map(str, BozoSort(vector, True))))
print(' '.join(map(str, BozoSort(vector, False))))
print(' '.join(map(str, BozoSort(matrix, True))))
print(' '.join(map(str, BozoSort(matrix, False))))
print(' '.join(map(str, BozoSortForThree(vector[0], vector[1], vector[2], True))))
print(' '.join(map(str, BozoSortForThree(vector[0], vector[1], vector[2], False))))