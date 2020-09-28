print('Введите число, возводимое в факториал')

a = int(input())
result = 1

for i in range(1, a + 1):
    result *= i

print(result)
