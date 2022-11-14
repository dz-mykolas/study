from math import floor


def main():
    number = int(input("Number: "))

    # Array of vendor dictionaries
    vendors = [
        {
            "name": "VISA",
            "length": [13, 16],
            "firstNum": [4]
        },
        {
            "name": "MASTERCARD",
            "length": [16],
            "firstNum": [51, 52, 53, 54, 55]
        },
        {
            "name": "AMEX",
            "length": [15],
            "firstNum": [34, 37]
        }]

    # Declare here empty in case it doesn't get assigned
    inputCard = {}

    # Assigns correct card according to number (if exists)
    for card in vendors:
        # Gets length of number in digits
        nLength = len(str(number))
        # Checks if such length exists
        if nLength in card["length"]:
            # Checks according to first digit
            if floor(number / pow(10, nLength - 1)) in card["firstNum"]:
                inputCard = card
                break
            # Checks according to first 2 digits
            if floor(number / pow(10, nLength - 2)) in card["firstNum"]:
                inputCard = card
                break

    # Checks if checkSum is valid and if card got assigned
    if checkSum(number) and inputCard in vendors:
        print(inputCard["name"])
    else:
        print("INVALID")


# Gets digits for checkSum() according to formula
def getDigits(cardNum):
    digList = []
    i = 1
    while cardNum > 1:
        if (i % 2) == 0:
            newDigit = (floor(cardNum) % 10) * 2
            while newDigit > 0:
                digList.append(newDigit % 10)
                newDigit = floor(newDigit / 10)
        else:
            digList.append(floor(cardNum) % 10)
        cardNum = cardNum / 10
        i += 1
    return digList


# Validates card according to formula (sum)
def checkSum(cardNum):
    sumDigits = sum(getDigits(cardNum))
    if (sumDigits % 10) == 0:
        return True
    else:
        return False


main()
