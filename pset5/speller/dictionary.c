// Implements a dictionary's functionality
#include<math.h>
#include <stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
//const unsigned int N = 1;
const unsigned int N = 26;

// Hash table
node *table[N];

long wordsize = 0;

int hashword(const char *wordindictionary);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int checkposition = hash(word);
    for (node *ht = table[checkposition]; ht != NULL; ht = ht->next)
    {
        if (strcasecmp(word, ht->word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int position = -1;
    position = hashword(word);
    return position;
    //return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    int loadsuccesstimes = 0;
    FILE *dictionaryfile = fopen(dictionary, "r");
    if (dictionaryfile == NULL)
    {
        return false;
    }

    char dictionaryword[LENGTH + 1];
    node *wordnode = NULL;
    int hashtableposition = -1;
    node *nextnode = NULL;
    while (fscanf(dictionaryfile, "%s", dictionaryword) != EOF)
    {
        wordnode = malloc(sizeof(node));
        if (wordnode == NULL)
        {
            return false;
        }
        //printf("dictionaryword: %s\n",dictionaryword);
        strcpy(wordnode->word, dictionaryword);
        wordnode->next = NULL;

        hashtableposition = hash(wordnode->word);
        //printf("hashtableposition: %i\n",hashtableposition);

        if (table[hashtableposition] == NULL)
        {
            table[hashtableposition] = wordnode;
            wordsize = wordsize + 1;
            loadsuccesstimes = loadsuccesstimes + 1;
        }
        else
        {
            nextnode = wordnode;
            nextnode->next = table[hashtableposition];
            table[hashtableposition] = nextnode;
            wordsize = wordsize + 1;
        }
    }

    /*for(int t = 0; t < 26; t = t + 1){
        if(table[t]!=NULL){

        }
    }*/

    fclose(dictionaryfile);

    if (loadsuccesstimes > 0)
    {
        return true;
    }
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (wordsize > 0)
    {
        return wordsize;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *nextunloadnode = NULL;
    node *currentunloadnode = NULL;
    long unloadtimes = 0;
    for (int u = 0; u < 26; u = u + 1)
    {
        nextunloadnode = table[u];
        currentunloadnode = nextunloadnode;
        while (nextunloadnode != NULL)
        {
            nextunloadnode = nextunloadnode->next;
            free(currentunloadnode);
            currentunloadnode = nextunloadnode;
            unloadtimes = unloadtimes + 1;
        }
    }
    if (unloadtimes == wordsize)
    {
        return true;
    }
    return false;
}

int hashword(const char *wordindictionary)
{
    int positioninhashtable = -1;
    char *capitalalphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *lowercasealphabet = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < 26; i = i + 1)
    {
        if (wordindictionary[0] == capitalalphabet[i] || wordindictionary[0] == lowercasealphabet[i])
        {
            positioninhashtable = i;
            i = 26;
        }
    }
    positioninhashtable = positioninhashtable % 26;
    return positioninhashtable;
}
