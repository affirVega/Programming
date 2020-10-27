n = int(input())
banknotes = []
for _ in range(n):
    banknote = input()
    if banknote.startswith('a') and banknote.endswith('55661'):
        banknotes.append(banknote)

if len(banknotes) == 0:
    print(-1)
else:
    print(' '.join(banknotes))
