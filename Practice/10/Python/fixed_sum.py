print("Введите сумму, границы первого промежутка и границы второго промежутка на одной строке через пробел")
s, l1, r1, l2, r2 = [int(x) for x in input().split()]

i = l1
j = r2

if (i + j < s):
    i = min(r1, s-j)
else:
    j = max(l2, s-i)

if (i + j < s):
    i = min(r1, s-j)
else:
    j = max(l2, s-i)

if i + j == s:
    print("x1 =", min(i, j), "\nx2 =", max(i, j))
else:
    print("Нет таких x")
