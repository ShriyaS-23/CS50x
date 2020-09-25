from cs50 import get_float  # importing get_float 

while True:
    change = get_float("Change Owed: ")  # taking input
    if change > 0:  # checking input is greater than 0
        break

cents = change * 100  # converting change into cents
coins = 0  # coin counter variable

while cents != 0:  # finding how many coins needed
    if cents >= 25:
        coins += 1
        cents = cents - 25
    elif cents >= 10:
        coins += 1
        cents = cents - 10
    elif cents >= 5:
        coins += 1
        cents = cents - 5
    else:
        coins += 1
        cents = cents - 1
        
print(f"{coins} coins")  # printing number of coins