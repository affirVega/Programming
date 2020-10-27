def get_numbers():
    return 37

def get_k():
    return 12

count = {}
round_appearance = {}
for i in range(get_numbers()):
    count[i] = round_appearance[i] = 0

highest_number = round_now = reds = blacks = 0
while (True):
    round_now += 1
    inpt = int(input())
    if inpt < 0:
        break

    count[inpt] += 1
    round_appearance[inpt] = round_now
    
    highest_number = max(count.values())
    for i in range(get_numbers()):
        if count[i] == highest_number:
            print(i, end = ' ')
    print()

    for i in range(get_numbers()):
        if round_appearance[i] == 0 or round_now-round_appearance[i]>get_k():
            print(i, end = ' ')
    print()

    if inpt != 0:
        if inpt <= 10 or (inpt > 18 and inpt <= 28):
            if inpt % 2 == 1: reds += 1
            else:             blacks += 1
        else:
            if inpt % 2 == 0: reds += 1
            else:             blacks += 1

    print(reds,blacks,'\n')
