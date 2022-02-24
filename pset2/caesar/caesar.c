#include<cs50.h>
#include<ctype.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int checkkey(string keytocheck, int lengthofkey);
string encrypt(string texttoencrypt, int lengthoftext, int keytoencrypt);

int main(int argc, string argv[])
{
    //asks user to run the program with command line argument.
    if (argc == 2)
    {
        string keytext;
        int key;
        int keylength;
        string plaintext;
        int plaintextlength;
        string encrypttext;

        //checks the key whether it is numeric or not.
        keytext = argv[1];
        keylength = strlen(keytext);
        key = checkkey(keytext, keylength);

        //encrypts text if the key is valid.
        if (key > 0)
        {
            //asks user to enter plaintext.
            plaintext = get_string("plaintext: ");
            plaintextlength = strlen(plaintext);

            //print out ciphertext based on the plaintext that the user has entered.
            encrypttext = encrypt(plaintext, plaintextlength, key);
            printf("ciphertext: %s\n", encrypttext);
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

        return 0;
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

}

int checkkey(string keytocheck, int lengthofkey)
{
    int encryptkey = 0;
    int keyisnumbertimes = 0;
    for (int i = 0; i < lengthofkey; i = i + 1)
    {
        if (isdigit(keytocheck[i]))
        {
            keyisnumbertimes = keyisnumbertimes + 1;
            //printf("Key is number.\n");
        }/*else{
            printf("Key is not number.\n");
        }*/
    }
    if (keyisnumbertimes == lengthofkey)
    {
        encryptkey = atoi(keytocheck);
        //printf("Success\n");
        //printf("%i\n",encryptkey);
    }
    else
    {
        printf("Usage: ./caesar key\n");
    }
    return encryptkey;
}

string encrypt(string texttoencrypt, int lengthoftext, int keytoencrypt)
{
    string changetext;
    string updatetext = texttoencrypt;
    string capitalalphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string lowercasealphabet = "abcdefghijklmnopqrstuvwxyz";
    int alphabetposition = 0;
    char encryptcharacter;

    for (int i = 0; i < lengthoftext; i = i + 1)
    {
        if (isalpha(updatetext[i]))
        {
            //updatetext[i] = updatetext[i] + keytoencrypt % 26;
            if (isupper(updatetext[i]))
            {
                for (int uc = 0; capitalalphabet[uc] != updatetext[i]; uc = uc + 1)
                {
                    alphabetposition = alphabetposition + 1;
                }
                //printf("Alphabet position: %i\n",alphabetposition);
                encryptcharacter = capitalalphabet[(alphabetposition + keytoencrypt) % 26];
                //printf("Encrypt character: %c\n",encryptcharacter);
                updatetext[i] = encryptcharacter;
                alphabetposition = 0;
            }
            else if (islower(updatetext[i]))
            {
                for (int lc = 0; lowercasealphabet[lc] != updatetext[i]; lc = lc + 1)
                {
                    alphabetposition = alphabetposition + 1;
                }
                //printf("Alphabet position: %i\n",alphabetposition);
                encryptcharacter = lowercasealphabet[(alphabetposition + keytoencrypt) % 26];
                //printf("Encrypt character: %c\n",encryptcharacter);
                updatetext[i] = encryptcharacter;
                alphabetposition = 0;
            }
        }
    }
    changetext = updatetext;

    return changetext;
}