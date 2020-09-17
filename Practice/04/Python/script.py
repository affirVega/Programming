a = int(input('Введите число: '))
b = int(input('Введите ещё одно число: '))

a, b = b, a

print('a =',a)
print('b =',b)

a = a - b
b = b + a
a = b - a

print('a =',a)
print('b =',b)
