import cs50


def main():
    # asks user for credit card.
    cardnumber = cs50.get_string("Number: ")
    cardlength = len(cardnumber)
    cardnumber = int(cardnumber)
    # print(cardlength)

    validcard = calculatecreditcard(cardnumber)

    if validcard == True:
        checkcardtype(cardnumber, cardlength)
    else:
        print("INVALID")


# calculates credit card checksum.
def calculatecreditcard(numberoncard):
    numberwithoutlastdigit = numberoncard / 10
    numberwithlastdigit = numberoncard
    cardchecksum = 0
    validchecksum = False

    # calculates the sum of digits multiply by 2.
    while numberwithoutlastdigit > 0:
        multiplydigit = int(numberwithoutlastdigit) % 10 * 2
        if(multiplydigit > 9):
            lastmultiplydigit = int(multiplydigit) % 10
            firstmultiplydigit = int(multiplydigit) / 10 % 10
            sumoffirstandlastmultiplydigits = int(firstmultiplydigit) + int(lastmultiplydigit)
            cardchecksum = cardchecksum + int(sumoffirstandlastmultiplydigits)
        else:
            cardchecksum = cardchecksum + int(multiplydigit)
        numberwithoutlastdigit = int(numberwithoutlastdigit) / 100

    # calculates the sum of digits that are not multiplied by 2.
    while numberwithlastdigit > 0:
        nomultiplydigit = int(numberwithlastdigit) % 10
        cardchecksum = cardchecksum + int(nomultiplydigit)
        numberwithlastdigit = int(numberwithlastdigit) / 100

    # calculates checksum is valid or not.
    if cardchecksum % 10 == 0:
        validchecksum = True
    else:
        validchecksum = False

    return validchecksum


# checks credit card is valid or not.
def checkcardtype(numberoncard, length):
    AmericanExpresslength = 15
    MasterCardlength = 16
    VisaCardlength = [13, 14, 15, 16]

    AmericanExpressstart = [34, 37]
    MasterCardstart = [51, 52, 53, 54, 55]
    VisaCardstart = 4

    numbertocheck = numberoncard
    lengthtocheck = length
    # checks if card is AMEX or not.
    if length == AmericanExpresslength:
        while lengthtocheck > 2:
            numbertocheck = int(numbertocheck) * 0.1
            lengthtocheck = lengthtocheck - 1
        numbertocheck = int(numbertocheck)
        if numbertocheck in AmericanExpressstart:
            print("AMEX")
    # checks if card is MASTERCARD or VISA.
    elif length == MasterCardlength or length == VisaCardlength[3]:
        while lengthtocheck > 2:
            numbertocheck = int(numbertocheck) * 0.1
            lengthtocheck = lengthtocheck - 1
        numbertocheck = int(numbertocheck)
        if numbertocheck in MasterCardstart:
            print("MASTERCARD")
        else:
            while lengthtocheck > 1:
                numbertocheck = int(numbertocheck) * 0.1
                lengthtocheck = lengthtocheck - 1
            numbertocheck = int(numbertocheck)
            if numbertocheck == VisaCardstart:
                print("VISA")
    # checks if card is VISA.
    elif length in VisaCardlength:
        while lengthtocheck > 1:
            numbertocheck = int(numbertocheck) * 0.1
            lengthtocheck = lengthtocheck - 1
        numbertocheck = int(numbertocheck)
        if numbertocheck == VisaCardstart:
            print("VISA")
    else:
        print("INVALID")

    # print("VALID")


main()
