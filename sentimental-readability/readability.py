# TODO
from cs50 import get_int, get_string

input = get_string("Text: ")
words = 0
letters = 0
sent = 0
for i in input:
    if i == " " :
        words += 1
        # print(i)
    elif i.isalpha():
        letters += 1
    elif i == '?' or i == '!' or i == '.':
        sent += 1

L = letters / (words+1) * 100
S = sent / (words+1) * 100

index = (0.0588 * L) - (0.296 * S) - 15.8
ans = round(index)


if ans > 16:
    print("Grade 16+")
if ans < 1:
    print("Before Grade 1")
if ans > 1 and ans < 16:
    print("Grade ",ans)



