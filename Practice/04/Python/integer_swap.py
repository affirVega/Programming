a = int(input("Введите число: "))
b = int(input("Введите ещё одно число: "))

# Обмен без дополнительной переменной
a, b = b, a

print("a =",a)
print("b =",b)

# Обмен с дополнительной переменной
temp = a
a = b
b = temp

print("a =",a)
print("b =",b)
