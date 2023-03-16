# TODO
from cs50 import get_int
while True:
    n = get_int("Height:")
    if n > 0 and n <= 8:
        break

for i in range (1, n+1):
    for j in range (i, n):
        print(" ", end = "")
    for j in range (i):
        print("#", end = "")
    print("  ", end = "")
    for j in range (i):
         print("#", end = "")
    print()
