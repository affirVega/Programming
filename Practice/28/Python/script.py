def print_factors(factors: dict) -> None:
    not_first = False
    for key, value in factors.items():
        if not_first:
            print("*", end="")
        else:
            not_first = True

        print(key, end="")

        if value > 1:
            print("^", value, sep='', end='')

    print()

def facrotization(n: int) -> None:
    factors = {}

    while True:
        cont = False
        for i in range(2, n + 1):
            if n == 0: break
            if n % i == 0:
                n //= i
                factors[i] = factors.get(i, 0) + 1
                
                cont = True
                break

        if not cont:
            break

    print_factors(factors)

facrotization(int(input("Введите число: ")))
