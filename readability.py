from cs50 import get_string
from sys import exit
import math

text = get_string("Text:\n")
l = 0
for i in range(len(text)):  # finding no. of letters
    if text[i].isalpha() == True: 
        l += 1

w = 1
for i in range(len(text)):  # finding no. of words
    if text[i] == " ":
        w += 1

s = 0
for i in range(len(text)):  # finding no. of sentences
    if text[i] == "." or text[i] == "!" or text[i] == "?":
        s += 1

L = float(l) / float(w) * 100
S = float(s) / float(w) * 100

read = round(0.0588 * L - 0.296 * S - 15.8)  # finding reading level

    
if read < 1:  # printing reading level
    print("Before Grade 1")
elif read > 16:
    print("Grade 16+")
else:
    print(f"Grade {read}")
    
