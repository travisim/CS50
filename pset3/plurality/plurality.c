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

// ________________________________________________________ ________________________________________________________
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // compares if two stings are same and if it is
        // then adds one vote to the candidate
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            // printf("Added Votes\n");
            return true;
        }


    }

    return false;
}

// ________________________________________________________ ________________________________________________________
void print_winner(void)
{
    // TODO

    int tvotes = 0;
    // prints winnwer by searching for largest votes amongst candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > tvotes)
        {
            tvotes = candidates[i].votes;
        }


    }
    for (int i = 0; i < candidate_count; i++)
        if (candidates[i].votes == tvotes)
        {
            printf("%s\n", candidates[i].name);
        }


    return;
}

