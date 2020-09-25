while True:
    h = int(input("Enter the Height:"))  # height input from user
    if h > 0 and h <= 8:
        break
    
for i in range(h):  # printing bricks
    for c in range(i, h-1):
        print(" ", end="")
    for d in range(i+1):
        print("#", end="")
    print("  ", end="")
    for x in range(i+1):
        print("#", end="")
    print()
    