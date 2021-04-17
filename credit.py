from cs50 import get_int

while True:
    CNum = get_int("Card Number: ")  # taking input
    if CNum > 0:  # checking input is greater than 0
        break

x = CNum
q = CNum
t = CNum
y = 0

while x != 0:
    b = (x % 100 - x & 10) / 10
    x = x / 100
    c = b * 2
    if c / 10 == 0:
        y = y + c
    else:
        while c != 0:
            f = c % 10
            y = y + f
            c = c / 10

s2 = 0
while q != 0:
    s2 = s2 + q %10
    q = q / 100

s = y + s2

# checking for type of card
if s % 10 == 0 and (1/10000000000000 == 34 or t / 10000000000000 == 37):
    print("AMEX")
elif s % 10 == 0 and (t / 100000000000000 == 51 or t / 100000000000000 == 52 or t / 100000000000000 == 53 or t / 100000000000000 == 54 or t / 100000000000000 == 55):
    print("MASTERCARD")
elif s % 10 == 0 and (t / 1000000000000 == 4 or t / 1000000000000000 == 4):
    print("VISA")
else:
    print("INVALID")