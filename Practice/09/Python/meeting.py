print('Введите 2 времени в формате \"ЧЧ:ММ\" каждое с новой строки')

a, b = [int(x) for x in input().split(sep=':')]
c, d = [int(x) for x in input().split(sep=':')]

a = 60 * a + b
c = 60 * c + d

if abs(a - c) > 15:
    print('Встреча не состоится')
else:
    print('Встреча состоится')
