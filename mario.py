from cs50 import get_int
while True:
    h = get_int("Enter the Height:")  # height input from user
    if h > 0 and h <= 8:
        break

for i in range(h):
    for c in range(i, h-1):  # printing space
        print(" ", end="")
    for j in range(i+1):  # printing bricks
        print("#", end="")
    print()  # moving to new line