#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

char CAPITALLETTERS[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char SMALLLETTERS[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

int check_character(char wordcharacter);
int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int check_character(char wordcharacter)
{
    int characterscore = 0;
    if (wordcharacter >= 'A' && wordcharacter <= 'Z')
    {
        for (int i = 0; i < 26; i = i + 1)
        {
            if (wordcharacter == CAPITALLETTERS[i])
            {
                characterscore = POINTS[i];
                //printf("character is '%c' and score is %i.\n",wordcharacter,characterscore);
            }
        }
    }
    else if (wordcharacter >= 'a' && wordcharacter <= 'z')
    {
        for (int i = 0; i < 26; i = i + 1)
        {
            if (wordcharacter == SMALLLETTERS[i])
            {
                characterscore = POINTS[i];
                //printf("character is '%c' and score is %i.\n",wordcharacter,characterscore);
            }
        }
    }
    else
    {
        characterscore = 0;
        //printf("character is '%c' and score is %i.\n",wordcharacter,characterscore);
    }
    return characterscore;
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int wordlength = strlen(word);
    int wordscore = 0;
    for (int i = 0; i < wordlength; i = i + 1)
    {
        wordscore = wordscore + check_character(word[i]);
    }
    return wordscore;
}
