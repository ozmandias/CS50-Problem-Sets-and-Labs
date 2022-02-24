#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];
bool resetpreferences = false;

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    bool candidateshavethesamename = false;

    if (resetpreferences == false)
    {
        for (int v = 0; v < voter_count; v = v + 1)
        {
            for (int r = 0; r < candidate_count; r = r + 1)
            {
                preferences[v][r] = -1;
                //printf("Voter %i's rank %i: %i\n",v,r,preferences[v][r]);
                //printf("Voter %i's rank %i: %i\n",v+1,r+1,preferences[v][r]);
            }
        }
        resetpreferences = true;
    }

    for (int i = 0; i < candidate_count; i = i + 1)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            for (int j = 0; j < candidate_count; j = j + 1)
            {
                if (preferences[voter][j] == i)
                {
                    //printf("%i\n",preferences[voter][j]);
                    candidateshavethesamename = true;
                }
            }
            if (candidateshavethesamename == false)
            {
                //printf("Valid vote.\n");
                preferences[voter][rank] = i;
                //printf("Voter %i's Rank %i: %i\n",voter+1,rank+1,preferences[voter][rank]);
                return true;
            }
        }
    }

    //printf("No two candidates can have the same name.\n");
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    int nextlocation = 1;
    bool nextcandidategetsvote = false;
    for (int v = 0; v < voter_count; v = v + 1)
    {
        /*for (int r = 0; r < candidate_count; r = r + 1)
        {
            for (int c = 0; c < candidate_count; c = c + 1)
            {
                if (preferences[v][r] == c)
                {
                    if (candidates[c].eliminated == false)
                    {
                        candidates[c].votes = candidates[c].votes + 1;
                        //printf("%s gets a vote.\n",candidates[c].name);
                        printf("Total votes for %s: %i\n",candidates[c].name,candidates[c].votes);
                    }
                }
            }
        }*/
        for (int c = 0; c < candidate_count; c = c + 1)
        {
            if (preferences[v][0] == c)
            {
                if (candidates[c].eliminated == false)
                {
                    candidates[c].votes = candidates[c].votes + 1;
                    //printf("Total votes for %s: %i\n", candidates[c].name, candidates[c].votes);
                }
                else
                {
                    for (int p = preferences[v][nextlocation]; nextcandidategetsvote == false; p = preferences[v][nextlocation])
                    {
                        if (candidates[p].eliminated == false)
                        {
                            candidates[p].votes = candidates[p].votes + 1;
                            nextcandidategetsvote = true;
                        }
                        nextlocation = nextlocation + 1;
                    }
                }
            }
        }
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    int halfofvotes = round(voter_count / 2);
    int winnerlocation = -1;
    bool foundwinner = false;
    //printf("Half of votes: %i\n",halfofvotes);
    for (int i = 0; i < candidate_count; i = i + 1)
    {
        if (candidates[i].votes > halfofvotes)
        {
            foundwinner = true;
            winnerlocation = i;
        }
    }
    if (foundwinner == true)
    {
        printf("%s\n", candidates[winnerlocation].name);
        return true;
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int minimumvotes = 0;
    bool foundminimumvotes = false;
    int candidatelocation = 0;
    do
    {
        if (candidates[candidatelocation].eliminated == false)
        {
            minimumvotes = candidates[candidatelocation].votes;
            //printf("Minimum votes at start: %i\n",minimumvotes);
        }
        if (candidatelocation < candidate_count)
        {
            candidatelocation = candidatelocation + 1;
        }
    }
    while (minimumvotes == 0);
    for (int i = 0; i < candidate_count; i = i + 1)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes < minimumvotes || candidates[i].votes == minimumvotes)
            {
                foundminimumvotes = true;
                minimumvotes = candidates[i].votes;
            }
        }
    }
    if (foundminimumvotes == true)
    {
        //printf("Minimum votes: %i\n",minimumvotes);
        return minimumvotes;
    }
    return 0;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    bool candidateshavesamevotes = false;
    int minvotestimes = 0;
    int candidatesinelectiontimes = 0;
    for (int i = 0; i < candidate_count; i = i + 1)
    {
        if (candidates[i].eliminated == false)
        {
            candidatesinelectiontimes = candidatesinelectiontimes + 1;
            if (candidates[i].votes == min)
            {
                minvotestimes = minvotestimes + 1;
            }
        }
    }
    if (minvotestimes == candidatesinelectiontimes)
    {
        candidateshavesamevotes = true;
    }
    if (candidateshavesamevotes == true)
    {
        //printf("Candidates have same votes.\n");
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i = i + 1)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes == min)
            {
                candidates[i].eliminated = true;
            }
        }
    }
    return;
}
