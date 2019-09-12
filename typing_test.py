""" Typing Test implementation """

from utils import *
from ucb import main

# BEGIN Q1-5
"*** YOUR CODE HERE ***"
def lines_from_file(path):
    file = open(path,mode='r')
    row = []
    row +=readlines(file)
    for i in range(len(row)):
        row[i] = row[i].strip()
    return row

def new_sample(path, i):
    paragraphs = lines_from_file(path)
    return paragraphs[i]

def analyze(sample_paragraph, typed_string, start_time, end_time):
    def words_per_min():
        num_character = [char for char in typed_string]
        num_words = len(num_character)/ 5
        wpm = num_words * 60 / (end_time - start_time)
        return wpm

    def accuracy_per():
        correct_words = 0
        typed_words = split(typed_string)
        actual_words = split(sample_paragraph)
        least_word = min(len(typed_words),len(actual_words))
        for x in range(least_word):
            if typed_words[x] == actual_words[x]:
                correct_words = correct_words + 1

        if least_word == 0:
            return 0.0
        return (correct_words/least_word) * 100

    return [words_per_min(),accuracy_per()]

def pig_latin(word):
    vowel = ['a','e','i','o','u']
    
    new_word, move_word = word, ''

    if word[0] not in vowel:
        for x in range(len(word)):
            if word[x] not in vowel:
                move_word += word[x]
                new_word = new_word[len(new_word)-(len(new_word)-1):]
            else:
                break
        return new_word + move_word + 'ay'
    else:
        return word + 'way'

def autocorrect(user_input, words_list, score_function):
    result = ""
    if user_input in words_list:
        result = user_input
    if result:
        return result
    return min(words_list, key = lambda x: score_function(user_input,x))

def swap_score(string1, string2):
    if min(len(string1),len(string2)) == 1:
        if string1[0] == string2[0]:
            return 0
        else:
            return 1
    else:
        if string1[0] == string2[0]:
            return 0 + swap_score(string1[1:],string2[1:])
        else:
            return 1 + swap_score(string1[1:],string2[1:])

# END Q1-5


# Question 6

def score_function(word1, word2):
    """A score_function that computes the edit distance between word1 and word2."""
    
    if not word1 or not word2:
        return len(word1) or len(word2)
    if word1[0] != word2[0]:
        remove_char = 1 + score_function(word1[1:], word2)
        add_char = 1 + score_function(word1, word2[1:])
        substitute_char = 1 + score_function(word2[0] + word1[1:], word2)
        return min(add_char,remove_char,substitute_char)
    return score_function(word1[1:], word2[1:])


KEY_DISTANCES = get_key_distances()

# BEGIN Q7-8
"*** YOUR CODE HERE ***"

def score_function_accurate(word1, word2):
    if not word1 or not word2:
        return len(word1) or len(word2)
    
    if word1[0] != word2[0]:
        remove_char = 1 + score_function_accurate(word1[1:], word2)
        add_char = 1 + score_function_accurate(word1, word2[1:])
        substitute_char = KEY_DISTANCES[word1[0], word2[0]] + score_function_accurate(word2[0] + word1[1:], word2)
        return min(remove_char,add_char,substitute_char)

    return score_function_accurate(word1[1:], word2[1:])

d = {}
def score_function_final(word1, word2):
    def helper(word1, word2):
        if not word1 or not word2:
            return len(word1) or len(word2)
        if word1[0] != word2[0]:
            if (word1,word2) in d:
                return d.get((word1,word2),0)
            elif (word2,word1) in d:
                return d.get((word2,word1),0)
            else:
                remove_char = 1 + helper(word1[1:], word2)
                add_char = 1 + helper(word1, word2[1:])
                substitute_char = KEY_DISTANCES[word1[0], word2[0]] + helper(word2[0] + word1[1:], word2)
                d[(word1,word2)] = min(remove_char,add_char,substitute_char)
                return min(remove_char,add_char,substitute_char)
        return helper(word1[1:], word2[1:])
    
    if (word1,word2) in d:
        return d.get((word1,word2),0)
    elif (word2,word1) in d:
        return d.get((word2,word1),0)
    else:
        d[(word1,word2)] = helper(word1,word2)
        return d.get((word1,word2),0)

# END Q7-8
