def x(x0, v0, a, t):
    return x0 + v0*t - (a*t*t) / 2

g = 9.8
x0 = int(input("Введите x0: "))
v0 = int(input("Введите v0: "))
t = int(input("Введите t: "))

d = abs(x0 - x(x0, v0, g, t))
print(d)

