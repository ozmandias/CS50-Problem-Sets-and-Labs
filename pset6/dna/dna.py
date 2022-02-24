import csv
import sys


def main():
    # checks if user has tyed in database file and sequence file correctly.
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        sys.exit(1)

    # stores STRs
    dnastr = {
        "AGATC": 0,
        "TTTTTTCT": 0,
        "AATG": 0,
        "TCTAG": 0,
        "GATA": 0,
        "TATC": 0,
        "GAAA": 0,
        "TCTG": 0
    }

    # opens database file into memory.
    dnadatabasefile = open(sys.argv[1], "r")
    dnadatabasereader = csv.reader(dnadatabasefile)
    next(dnadatabasereader)

    # opens sequence file into memory.
    dnasequencefile = open(sys.argv[2], "r")
    dnasequencetext = dnasequencefile.read()
    dnasequencetextlength = len(dnasequencetext)
    # print(dnasequencetext)
    # print(len(dnasequencetext))

    # checks how many STRs are repeated in  dna sequence.
    dnastr = checkstr(dnasequencetext, dnastr)
    # print(dnastr)
    dnasequencefile.close()

    # compares dna database and dna sequence.
    comparedna(dnadatabasereader, dnastr, dnadatabasefile)


def checkstr(dnasequencetocheck, dnastrtocheck):
    updatednastr = dnastrtocheck
    strrepeattimes = 0
    longestrepeattimes = 0

    for dnastrkey in dnastrtocheck:
        i = 0
        while i < len(dnasequencetocheck):
            if dnasequencetocheck[i:i+len(dnastrkey)] == dnastrkey:
                strrepeattimes = strrepeattimes + 1
                if longestrepeattimes < strrepeattimes:
                    longestrepeattimes = strrepeattimes
                i = i + len(dnastrkey)
            else:
                i = i + 1
                strrepeattimes = 0
        updatednastr[dnastrkey] = updatednastr[dnastrkey] + longestrepeattimes
        longestrepeattimes = 0
    return updatednastr


def comparedna(dnafilereader, strtoread, databasefile):
    for row in dnafilereader:
        if row[1] == str(strtoread["AGATC"]) and row[2] == str(strtoread["AATG"]) and row[3] == str(strtoread["TATC"]):
            print(row[0])
            databasefile.close()
            sys.exit(0)
        if row[1] == str(strtoread["AGATC"]) and row[2] == str(strtoread["TTTTTTCT"]) and row[3] == str(strtoread["AATG"]) and row[4] == str(strtoread["TCTAG"]) and row[5] == str(strtoread["GATA"]) and row[6] == str(strtoread["TATC"]) and row[7] == str(strtoread["GAAA"]) and row[8] == str(strtoread["TCTG"]):
            print(row[0])
            databasefile.close()
            sys.exit(0)
    print("No match")
    databasefile.close()
    sys.exit(0)


main()