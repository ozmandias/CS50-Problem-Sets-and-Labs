#include<cs50.h>
#include<stdio.h>

bool calculatecreditcard(long cardnumbertocalculate);
int findcardlength(long cardnumbertofindlength);
void checkcardtype(long cardnumbertochecktype, int lengthofcardnumbertocheck);

int main(void)
{
    long creditcardnumber;
    int cardlength;
    bool validcard = false;

    creditcardnumber = get_long("Number: ");
    cardlength = findcardlength(creditcardnumber);
    //printf("Length: %i\n",cardlength);
    validcard = calculatecreditcard(creditcardnumber);
    if (validcard == true)
    {
        //printf("Check card type.\n");
        checkcardtype(creditcardnumber, cardlength);
    }
    else
    {
        //printf("Invalid\n");
        printf("INVALID\n");
    }
}

bool calculatecreditcard(long cardnumbertocalculate)
{
    long cardnumberwithoutlastdigit = cardnumbertocalculate / 10;
    //printf("Card number without last digit: %li\n",cardnumberwithoutlastdigit);
    long cardnumberwithlastdigit = cardnumbertocalculate;
    //printf("Card number with last digit %li\n",cardnumberwithlastdigit);
    bool validchecksum = false;
    int creditcardchecksum = 0;
    int digitmultiplybytwo;
    int digitnotmultiplybytwo;

    while (cardnumberwithoutlastdigit > 0)
    {
        digitmultiplybytwo = cardnumberwithoutlastdigit % 10 * 2;
        //printf("Digit multiply by two: %i\n",digitmultiplybytwo);
        if (digitmultiplybytwo > 9)
        {
            int lastdigitofdigitmultiplybytwo = digitmultiplybytwo % 10;
            //printf("Last Digit: %i\n",lastdigitofdigitmultiplybytwo);
            int firstdigitofdigitmultiplybytwo = digitmultiplybytwo / 10 % 10;
            //printf("First Digit: %i\n",firstdigitofdigitmultiplybytwo);
            int sumoffirstandlastdigits = firstdigitofdigitmultiplybytwo + lastdigitofdigitmultiplybytwo;
            //printf("Sum of two digits: %i\n",sumoffirstandlastdigits);
            creditcardchecksum = creditcardchecksum + sumoffirstandlastdigits;
            //printf("Checksum: %i\n",creditcardchecksum);
        }
        else
        {
            creditcardchecksum = creditcardchecksum + digitmultiplybytwo;
            //printf("Checksum: %i\n",creditcardchecksum);
        }
        cardnumberwithoutlastdigit = cardnumberwithoutlastdigit / 100;
        //printf("Card number without last digit: %li\n",cardnumberwithoutlastdigit);
    }

    //printf("\n");

    while (cardnumberwithlastdigit > 0)
    {
        digitnotmultiplybytwo = cardnumberwithlastdigit % 10;
        //printf("Digit not multiply by two: %i\n",digitnotmultiplybytwo);
        creditcardchecksum = creditcardchecksum + digitnotmultiplybytwo;
        //printf("Checksum: %i\n",creditcardchecksum);
        cardnumberwithlastdigit = cardnumberwithlastdigit / 100;
        //printf("Card number with last digit: %li\n",cardnumberwithlastdigit);
    }

    //printf("\n");


    if (creditcardchecksum % 10 == 0)
    {
        validchecksum = true;
        //printf("Valid.\n");
    }
    else
    {
        validchecksum = false;
        //printf("Not Valid.\n");
    }
    return validchecksum;
}

int findcardlength(long cardnumbertofindlength)
{
    int cardnumberlength;
    for (long i = 1; i <= cardnumbertofindlength; i = i * 10)
    {
        /*if(i<cardnumbertofindlength){
            printf("i Count: %li\n",i);
        }*/
        if (cardnumberlength <= i)
        {
            cardnumberlength = cardnumberlength + 1;
            //printf("Length: %i\n",cardnumberlength);
        }
    }

    return cardnumberlength;
}

void checkcardtype(long cardnumbertochecktype, int lengthofcardnumbertocheck)
{
    int AmericanExpresslength = 15;
    int MasterCardlength = 16;
    int VisaCardlength1 = 13;
    int VisaCardlength2 = 14;
    int VisaCardlength3 = 15;
    int VisaCardlength4 = 16;

    int AmericanExpressstartdigits1 = 34;
    int AmericanExpressstartdigits2 = 37;
    int MasterCardstartdigits1 = 51;
    int MasterCardstartdigits2 = 52;
    int MasterCardstartdigits3 = 53;
    int MasterCardstartdigits4 = 54;
    int MasterCardstartdigits5 = 55;
    int VisaCardstartdigits = 4;

    long cardstartdigits = cardnumbertochecktype;

    if (lengthofcardnumbertocheck == AmericanExpresslength)
    {
        while (lengthofcardnumbertocheck > 2)
        {
            cardstartdigits = cardstartdigits * 0.1;//printf("Card number to check type: %li\n",cardstartdigits);
            lengthofcardnumbertocheck = lengthofcardnumbertocheck - 1;
        }
        if (cardstartdigits == AmericanExpressstartdigits1 || cardstartdigits == AmericanExpressstartdigits2)
        {
            //printf("AmericanExpress\n");
            printf("AMEX\n");
        }
        else
        {
            //printf("Invalid\n");
            printf("INVALID\n");
        }
    }
    else if (lengthofcardnumbertocheck == MasterCardlength || lengthofcardnumbertocheck == VisaCardlength4)
    {
        while (lengthofcardnumbertocheck > 2)
        {
            cardstartdigits = cardstartdigits * 0.1;//printf("Card number to check type: %li\n",cardstartdigits);
            lengthofcardnumbertocheck = lengthofcardnumbertocheck - 1;
        }
        if (cardstartdigits == MasterCardstartdigits1 || cardstartdigits == MasterCardstartdigits2
            || cardstartdigits == MasterCardstartdigits3 || cardstartdigits == MasterCardstartdigits4
            || cardstartdigits == MasterCardstartdigits5)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            while (lengthofcardnumbertocheck > 1)
            {
                cardstartdigits = cardstartdigits * 0.1;//printf("Card number to check type: %li\n",cardstartdigits);
                lengthofcardnumbertocheck = lengthofcardnumbertocheck - 1;
            }
            if (cardstartdigits == VisaCardstartdigits)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        //printf("MasterCard or Visa\n");
    }
    else if (lengthofcardnumbertocheck == VisaCardlength1 || lengthofcardnumbertocheck == VisaCardlength2
             || lengthofcardnumbertocheck == VisaCardlength3)
    {
        while (lengthofcardnumbertocheck > 1)
        {
            cardstartdigits = cardstartdigits * 0.1;//printf("Card number to check type: %li\n",cardstartdigits);
            lengthofcardnumbertocheck = lengthofcardnumbertocheck - 1;
        }
        if (cardstartdigits == VisaCardstartdigits)
        {
            //printf("Visa\n");
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }
    else
    {
        //printf("Invalid\n");
        printf("INVALID\n");
    }
}