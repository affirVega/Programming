import math

def is_prime(n):
    if n <= 3:
        return True

    if n % 2 == 0 or n % 3 == 0:
        return False

    for i in range(5, int(math.sqrt(n)+1), 6):
        if n % i == 0 or n % (i + 2) == 0:
            return False

    return True

if is_prime(int(input('Введите число для проверки\n'))):
    print("Простое")
else:
    print("Составное")
