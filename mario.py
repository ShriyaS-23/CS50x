
h = int(input("Enter the Height:\n"))  # height input from user

for i in range(h):
    for c in range(i, h-1):  # printing space
        print(" ", end="")
    for j in range(i):  # printing bricks
        print("#", end="")
    print()  # moving to new line