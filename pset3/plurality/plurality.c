#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i = i + 1)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes = candidates[i].votes + 1;
            //printf("Found\n");
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int greatestvotenumber = 0;
    int winnerposition = 0;
    string nameofwinner;
    int samenumberofvotestimes = 0;
    int samegreatestvotenumber = 0;
    bool tie = false;
    for (int i = 0; i < candidate_count; i = i + 1)
    {
        if (candidates[i].votes > greatestvotenumber)
        {
            greatestvotenumber = candidates[i].votes;
            winnerposition = i;
        }
        else if (candidates[i].votes == greatestvotenumber)
        {
            samenumberofvotestimes = samenumberofvotestimes + 1;
            samegreatestvotenumber = greatestvotenumber;
        }
    }

    if (greatestvotenumber > samegreatestvotenumber && greatestvotenumber != 0)
    {
        tie = false;
    }
    else if (greatestvotenumber == samegreatestvotenumber && samegreatestvotenumber != 0)
    {
        tie = true;
    }

    if (tie == false)
    {
        if (greatestvotenumber > 0)
        {
            nameofwinner = candidates[winnerposition].name;
            printf("%s\n", nameofwinner);
        }
    }
    else
    {
        //printf("Tie\n");
        string winners[samenumberofvotestimes];
        int winnersposition = 0;
        for (int t = 0; t < candidate_count; t = t + 1)
        {
            if (candidates[t].votes == samegreatestvotenumber)
            {
                winners[winnersposition] = candidates[t].name;
                winnersposition = winnersposition + 1;
            }
        }
        for (int tw = 0; tw <= samenumberofvotestimes; tw = tw + 1)
        {
            printf("%s\n", winners[tw]);
        }
    }
    return;
}

