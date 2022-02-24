#include<cs50.h>
#include<ctype.h>
#include<math.h>
#include<stdio.h>
#include<string.h>

int countletters(string texttocountletters, int lengthoftext);
int countwords(string texttocountwords, int lengthoftext);
int countsentences(string texttocountwords, int lengthoftext);
int calculatereadability(int lettersoftext, int wordsoftext, int sentencesoftext);

int main(void)
{
    string text;
    int letters;
    int words;
    int sentences;
    int textreadability;

    //asks user for text.
    text = get_string("Text: ");
    int textlength = strlen(text);

    //counts letters, words and sentences from the text that the user has entered.
    letters = countletters(text, textlength);
    words = countwords(text, textlength);
    sentences = countsentences(text, textlength);

    //calculates readability of the text
    textreadability = calculatereadability(letters, words, sentences);

    //prints out the reading level of the text according to the readability.
    if (textreadability < 16 && textreadability > 1)
    {
        printf("Grade %i\n", textreadability);
    }
    else if (textreadability >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }
}

int countletters(string texttocountletters, int lengthoftext)
{
    int lettersintext = 0;
    for (int i = 0; i < lengthoftext; i = i + 1)
    {
        if (isalpha(texttocountletters[i]))
        {
            lettersintext = lettersintext + 1;
        }
    }
    //printf("%i letter(s)\n", lettersintext);
    return lettersintext;
}

int countwords(string texttocountwords, int lengthoftext)
{
    int wordsintext = 1;
    for (int i = 0; i < lengthoftext; i = i + 1)
    {
        if (texttocountwords[i] == ' ')
        {
            if (isalpha(texttocountwords[i + 1]))
            {
                wordsintext = wordsintext + 1;
            }
            else if (texttocountwords[i + 1] >= 33 && texttocountwords[i + 1] <= 126)
            {
                wordsintext = wordsintext + 1;
            }
        }
    }
    //printf("%i word(s)\n", wordsintext);
    return wordsintext;
}

int countsentences(string texttocountsentences, int lengthoftext)
{
    int sentencesintext = 0;
    for (int i = 0; i < lengthoftext; i = i + 1)
    {
        if (texttocountsentences[i] == '.' || texttocountsentences[i] == '!' || texttocountsentences[i] == '?')
        {
            sentencesintext = sentencesintext + 1;
        }
    }
    //printf("%i sentence(s)\n", sentencesintext);
    return sentencesintext;
}

int calculatereadability(int lettersoftext, int wordsoftext, int sentencesoftext)
{
    float readabilityoftext = 0;
    int readabilityindex = 0;
    float LetterofReadability;
    float SentenceofReadability;

    LetterofReadability = ((float)lettersoftext / (float)wordsoftext) * 100;
    //printf("LetterofReadability: %f\n", LetterofReadability);
    SentenceofReadability = ((float)sentencesoftext / (float)wordsoftext) * 100;
    //printf("SentenceofReadability: %f\n", SentenceofReadability);

    readabilityoftext = 0.0588 * LetterofReadability - 0.296 * SentenceofReadability - 15.8;
    //printf("ReadabilityofText: %f\n", readabilityoftext);
    readabilityindex = round(readabilityoftext);
    //printf("ReadabilityIndex: %i\n", readabilityindex);
    return readabilityindex;
}