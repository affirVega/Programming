MINUTES_IN_HOUR = 60

print('Введите 2 времени в формате \"ЧЧ:ММ\" каждое с новой строки')

h1, m1 = map(int, input().split(sep=':'))
h2, m2 = map(int, input().split(sep=':'))

m1 = MINUTES_IN_HOUR * h1 + m1
m2 = MINUTES_IN_HOUR * h1 + m2

if abs(m1 - m2) > 15:
    print('Встреча не состоится')
else:
    print('Встреча состоится')
