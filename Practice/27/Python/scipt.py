n = int(input("Введите число n: ").strip())
values = map(int, input("Введите n чисел, разделённые пробелом:\n> ").strip().split(" "))

vec = []

for elem in values:
    for j in range(6):
        if j >= len(vec) or j == 5:
            break
        
        if elem > vec[j]:
            vec.insert(j, elem)
            break

    if j == 5 or j == len(vec):
        vec.append(elem)

    if len(vec) > 5:
        vec.pop(0)

    for item in vec: print(item, end=" ")
    print()
