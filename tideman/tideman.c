#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

// Merge Sort function prototypes
void merge(pair arr[], int start, int middle, int end);
void merge_sort(pair arr[], int start, int end);

// Cycle check funtion prototypes
bool cycle(int i);
bool cycle_check(int i, bool visited[]);

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
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i=0; i<candidate_count; i++) {
        if (strcmp(name, candidates[i]) == 0) {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count-1; i++) {
        for (int j = i+1; j < candidate_count; j++) {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            // initialize a pair
            pair pairing;

            // check for preference
            if (preferences[i][j] > preferences[j][i]) {
                pairing.winner = i;
                pairing.loser = j;

                pairs[pair_count] = pairing;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // sort pairs
    merge_sort(pairs, 0, pair_count-1);

    // pairs are sorted from least margin to greatest margin
    // reverse pairs so that they are sorted from greatest margin to least margin
    pair temp_pairs[pair_count];

    for (int i = 0; i < pair_count; i++) {
        temp_pairs[pair_count-1-i] = pairs[i];
    }
    for (int i = 0; i < pair_count; i++) {
        pairs[i] = temp_pairs[i];
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++) {
        // assume that given lock is true to check for cycle
        locked[pairs[i].winner][pairs[i].loser] = true;
        // if a cycle is found due to new lock then "unlock" and continue
        if (cycle(pairs[i].winner)) {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++) {
        // assume true until false
        bool winner = true;
        for (int j = 0; j < candidate_count; j++) {
            // if a candidate is a "loser" and pointed to in the graph return false
            if (locked[j][i] == true) {
                winner = false;
                break;
            }
        }
        // print root node of directed candidates graph
        if (winner) {
            printf("%s\n", candidates[i]);
            break;
        }
    }
}


// merge subarrays
// variable start is not rudundant as it will not equal 0 after first split
void merge(pair arr[], int start, int middle, int end)
{
    int len1 = middle-start+1;
    int len2 = end-middle;

    pair arr1[len1], arr2[len2];

    for (int i = 0; i < len1; i++)
        arr1[i] = arr[start+i];
    for (int j = 0; j < len2; j++)
        arr2[j] = arr[middle+1+j];

    int i = 0; 
    int j = 0;
    int k = start;

    while (i < len1 && j < len2) {
        int margin1 = preferences[arr1[i].winner][arr1[i].loser]-preferences[arr1[i].loser][arr1[i].winner];
        int margin2 = preferences[arr2[j].winner][arr2[j].loser]-preferences[arr2[j].loser][arr2[j].winner];
        if (margin1 <= margin2) {
            arr[k] = arr1[i];
            i++;
        }
        else {
            arr[k] = arr2[j];
            j++;
        }
        k++;
    }

    // add leftover elements to their respective subarrays
    while (i < len1) {
        arr[k] = arr1[i];
        i++;
        k++;
    }

    while (j < len2) {
        arr[k] = arr2[j];
        j++;
        k++;
    }
}

void merge_sort(pair arr[], int start, int end)
{
    if (start < end) {
        int middle = start+(end-start)/2;

        // sort subarrays
        merge_sort(arr, start, middle);
        merge_sort(arr, middle+1, end);

        // merge subarrays opposite to split pattern
        merge(arr, start, middle, end);
    }
}

// search for cycle of directed graph locked
bool cycle_check(int i, bool visited[]) {
    if(visited[i]) {
        return true;
    }
    else {
        visited[i] = true;
    }

    for(int j = 0; j < candidate_count; ++j) {
        if(locked[i][j] && cycle_check(j, visited)) {
            return true;
        }
    }
    return false;
}

bool cycle(int i) {
    bool visited[candidate_count];
    for(int j = 0; j < candidate_count; ++j)
        visited[j] = false;
    return cycle_check(i, visited);
}