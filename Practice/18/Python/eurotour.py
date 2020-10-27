import string
words = ["hallo", "klempner", "das", "ist", "fantastisch", "fluggegecheimen"]
chances = {}
count_in_words = {}
for letter in string.ascii_lowercase:
    chances[letter] = count_in_words[letter] = 0

overall_length = 0
for word in words:
    overall_length += len(word)
    for char in word:
        count_in_words[char] += 1

for char in count_in_words:
    chances[char] = count_in_words[char] / overall_length

word = input()

pronounce_chance = chances[word[0]]
if pronounce_chance == 0:
    print('First character is unknown')
    exit()

prev_chance = pronounce_chance

for i in range(1, len(word)):

    if chances[word[i]] == 0.0:

        if prev_chance == 0.0:

            print("Error: character at index",i,"is not known!")
            exit()

        else:
            pronounce_chance *= prev_chance
    
    else:
        pronounce_chance *= chances[word[i]]
        prev_chance = pronounce_chance

print(pronounce_chance)
