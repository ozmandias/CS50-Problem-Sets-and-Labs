import cs50

# asks user the amount of change.
changeowed = cs50.get_float("Change owed: ")
# asks user the amount of change again if change is a negative number.
while changeowed < 0.0:
    changeowed = cs50.get_float("Change owed: ")

# convert the amount of change to coin.
changeowed = round(changeowed * 100)

# calculates the amount of coins to give back to the user.
totalcoins = 0
while changeowed > 0.0:
    if changeowed >= 25:
        changeowed = changeowed - 25
        totalcoins = totalcoins + 1
    elif changeowed >= 10:
        changeowed = changeowed - 10
        totalcoins = totalcoins + 1
    elif changeowed >= 5:
        changeowed = changeowed - 5
        totalcoins = totalcoins + 1
    elif changeowed >= 1:
        changeowed = changeowed - 1
        totalcoins = totalcoins + 1

# prints the amount of coins to give back to the user.
print(totalcoins)