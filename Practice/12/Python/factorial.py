print("Введите число для расчёта факториала")

a = int(input())
result = 1

for i in range(2, a + 1):
    result *= i

print(result)
