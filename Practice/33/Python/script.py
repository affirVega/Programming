import sys
import builtins

def create(length, start = 0, inc = 0):
    if length < 0:
        print('Cannot create array with length ', length, '.', sep='', file=sys.stderr)
        return [];
    return [i for i in range(start, start + inc*length, inc)]

def sort(array, length):
    if length < 0:
        print('Cannot sort array with length ', length, '.', sep='', file=sys.stderr)
        return array;
    for i in range(1, length):
        for j in range(i, 1, -1):
            if array[j] < array[j-1]:
                array[j], array[j-1] = array[j-1], array[j]
    return array

def print(array, length):
    if length < 0:
        builtins.print('Cannot sort array with length ', length, '.', sep='', file=sys.stderr)
        return array;
    if length == 0:
        builtins.print('[]')
        return array;
    builtins.print('[', array[0], sep='', end='')
    for i in range(1, length):
        builtins.print(', ', array[i], sep='', end='')
    builtins.print(']')
    return array

builtins.print('Enter length, begin value and increment');
length = int(input())
start = int(input())
inc = int(input())
arr = create(length, start, inc)
sort(arr, length)
print(arr, length)

