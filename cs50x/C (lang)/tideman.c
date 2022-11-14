#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void printLocked();

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    printLocked();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Loops through
    for (int i = 0; i < candidate_count; i++)
    {
        // Checks if new name is on candidate list
        if (!strcmp(name, candidates[i]))
        {
            ranks[rank] = i;
            return true;
        }
    }
    // Returns false if can't find on candidates list
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Double for to loop through matrix
    for (int i = 0; i < candidate_count - 1; i++)
    {
        // j starts at i+1 because don't need to add current or before
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Double for to loop through matrix
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // if/else diagonal checking for which is higher
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Double for to do Selection sort
    for (int i = 0; i < pair_count; i++)
    {
        // Sets highest to first current instances
        int highestS = preferences[pairs[i].winner][pairs[i].loser];
        int highest = i;

        for (int j = i + 1; j < pair_count; j++)
        {
            // if found new higher set to new
            if (preferences[pairs[j].winner][pairs[j].loser] > highestS)
            {
                highestS = preferences[pairs[j].winner][pairs[j].loser];
                highest = j;
            }
        }

        // Saves to new temp variable for swapping
        // Swaps the 2 values.
        // If highest is current instance swaps itself (doesn't change anything)
        pair temp = pairs[i];
        pairs[i] = pairs[highest];
        pairs[highest] = temp;
    }
}


// https://gist.github.com/nicknapoli82/6c5a1706489e70342e9a0a635ae738c9
bool isInCycle(int winner, int loser)
{
    // Checks if already in cycle and instantly returns true if locked already
    if (locked[loser][winner])
    {
        return true;
    }

    // Recursive loop
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] && isInCycle(winner, i))
        {
            return true;
        }
    }
    // Returns false if not found
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Loops through pairs
    for (int i = 0; i < pair_count; i++)
    {
        // If returns false locks new pair
        if (!isInCycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Temporary bool that prevents printing from happening until found in locked
        bool temp = true;
        for (int j = 0; j < candidate_count; j++)
        {
            // Loops through locked until finds true
            // If finds sets temp to false, stops current loop and increments i to continue again
            if (locked[j][i])
            {
                temp = false;
                break;
            }
        }
        // If temp not changed prints current i candidate
        if (temp)
        {
            printf("%s\n", candidates[i]);
        }
    }
}

void printLocked()
{
    for (int i = 0; i < candidate_count; i++)
    {
       for (int j = 0; j < candidate_count; j++)
        {
            printf("%d ", locked[i][j]);
        }
        printf("\n");
    }
}