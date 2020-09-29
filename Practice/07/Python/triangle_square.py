import math

def length(x1, y1, x2, y2):
    return math.sqrt((x1 - x2)**2 + (y1 - y2)**2)

print("""Это программа для высчитывания площади треугольника.
Введите цифру, чтобы указать, какой тип данных о треугольнике вы хотите указать.
1. Длины стороны треугольника.
2. Координаты треугольника.""")

a = b = c = 0.0
inp = int(input())
if inp == 1:
    print("Введите длины сторон треугольника, каждое с отдельной строки.")
    a = float(input())
    b = float(input())
    c = float(input())
elif inp == 2:
    print("Введите три пары вещественных чисел, каждая пара с новой строки,\n" + 
        "числа в паре разделены пробелом. Первое число x, второе y.", sep='')
    x1, y1 = map(float, input().split())
    x2, y2 = map(float, input().split())
    x3, y3 = map(float, input().split())
    
    a = length(x1, y1, x2, y2)
    b = length(x2, y2, x3, y3)
    c = length(x3, y3, x1, y1)

p = (a + b + c) / 2
S = math.sqrt(p * (p - a) * (p - b) * (p - c))

print("S =", S)
