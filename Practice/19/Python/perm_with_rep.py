def print_permutations(usages, string, result, last, index, repetition_left):
    
    for k in usages:
        if (usages[k] - 1 > repetition_left):
            continue
        result[index] = k
        usages[k] += 1
        if last == index:
            print(''.join(result), end=' ')
        else:
            is_repeated = usages[k] > 1
            print_permutations(usages, string, result, last, index+1, repetition_left - is_repeated)
    
        usages[k] -= 1
    

def start(n, string):

        usages = {}
        result = []

        for _ in range(n):
            result += ' '

        for char in string:
            usages[char] = 0

        print_permutations(usages, string, result, n-1, 0, n - len(string))
        print()
	

n = int(input("Введите n: "))
string = input("Введите символы: ")

start(n, string)
