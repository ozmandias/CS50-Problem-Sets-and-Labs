import cs50

# asks user for the height of the pyramid.
pyramidheight = cs50.get_int("Height: ")
# asks user the height of the pyramid again if height is not 1 and 8 inclusive.
while pyramidheight < 1 or pyramidheight > 8:
    pyramidheight = cs50.get_int("Height: ")

# prints pyramid based on height.
for i in range(0, pyramidheight):
    # prints spaces while printing a row of pyramid.
    for ls in range(pyramidheight-1, i, -1):
        print(" ", end="")
    # prints left hashes while printing a row of pyramid.
    for lh in range(0, i + 1):
        print("#", end="")
    # prints two spaces at the middle while printing a row of pyramid.
    print("  ", end="")
    # ptints right hashes while printing a row of pyramid.
    for rh in range(0, i + 1):
        print("#", end="")
    # prints next line at the end of a row of pyramid.
    print()