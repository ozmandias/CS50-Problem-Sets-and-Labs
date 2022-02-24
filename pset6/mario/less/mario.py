import cs50

# asks user for the height of the pyramid.
pyramidheight = cs50.get_int("Height: ")
# asks user for the height again if height is not an integer between 1 and 8 inclusive.
while pyramidheight < 1 or pyramidheight > 8:
    pyramidheight = cs50.get_int("Height: ")

# prints pyramid based on height.
for i in range(0, pyramidheight):
    # prints spaces while printing a row of pyramid.
    for s in range(pyramidheight-1, i, -1):
        print(" ", end="")
    # prints hashes while printing a row of pyramid.
    for h in range(0, i + 1):
        print("#", end="")
    # prints next line at the end of a row of pyramid.
    print()