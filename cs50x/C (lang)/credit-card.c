// https://cs50.harvard.edu/x/2022/psets/1/credit/

#include <cs50.h>
#include <stdio.h>
#include <math.h>

int findLength(long int num);
bool checkSum(long int cardNum);
string checkProvider(int length, long cardNum);
string findValid(long int cardNum);
long int askNumber();

int main(void)
{
    long int cardNum = askNumber();
    printf("%s", findValid(cardNum));
}

// Returns the length of the number
int findLength(long int num)
{
    int length = 0;
    do
    {
        num /= 10;
        length++;
    }
    while (num != 0);
    return length;
}

// Finds checksum and if valid
bool checkSum(long int cardNum)
{
    int sum = 0;
    int i = 1;
    
    // Loop through whole number
    while (cardNum > 0)
    {
        // Check if every second from last
        if (i%2 == 0)
        {
            int temp = 2 * (cardNum % 10);
            if (temp >= 10)
            {
                sum += 1;
            }
            sum += temp % 10;
            cardNum /= 10;
        }
        else
        {
            sum += (cardNum % 10);
            cardNum /= 10;
        }
        i++;
    }

    // If checksum valid returns true; else false
    if (sum % 10 == 0)
    {
        return true;
    }
    return false;
}

// Finds which provider or if none
string checkProvider(int length, long cardNum)
{
    // Switch statement for different length of card numbers
    switch (length)
    {
        // Length 13 (VISA)
        case 13:
        {
            int startNum = (cardNum / ((long)pow(10, 12)));
            if (startNum == 4)
            {
                return "VISA\n";
            }
            else
            {
                return "INVALID\n";
            }
        }

        // Length 15 (AMEX)
        case 15:
        {
            int startNum = cardNum / (long)pow(10, 13);
            switch (startNum)
            {
                case 34:
                    return "AMEX\n";
                case 37:
                    return "AMEX\n";
                default:
                    return "INVALID\n";
            }
        }

        // Length 16 (VISA and MasterCard)
        case 16:
        {
            int startNum = cardNum / (long)pow(10, 15);

            // Checks if card is VISA
            if (startNum == 4)
            {
                return "VISA\n";
            }
            // Else checks for MasterCard if not returns INVALID
            else
            {
                startNum = cardNum / (long)pow(10, 14);
                switch (startNum)
                {
                    case 51:
                        return "MASTERCARD\n";
                    case 52:
                        return "MASTERCARD\n";
                    case 53:
                        return "MASTERCARD\n";
                    case 54:
                        return "MASTERCARD\n";
                    case 55:
                        return "MASTERCARD\n";
                    default:
                        return "INVALID\n";
                }
            }
        }
        default:
            return "INVALID\n";
    }
}

// Finds if card is valid
string findValid(long int cardNum)
{
    int length = findLength(cardNum);
    bool checkSum_t = checkSum(cardNum);
    //Checks if check
    if (checkSum_t)
    {
        return checkProvider(length, cardNum);
    }
    return "INVALID\n";
}

// Asks the user to input Credit Card number
long int askNumber()
{
    long int cardNum = 0;
    cardNum = get_long("Please enter Credit Card number: ");
    return cardNum;
}
