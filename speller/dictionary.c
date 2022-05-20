// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

const unsigned int N = 65536;

// Hash table
node *table[N];

int dict_size = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // create blank array that is the same size as word
    char *_word = malloc(LENGTH+1);

    // copy word to array of lowercase chars only
    for (int i = 0; i < LENGTH+1; i++) {
        _word[i] = tolower(word[i]);
        // break at end of word
        if (word[i] == '\0') {
            break;
        }
    }

    // get root node for linked list
    node *_node = table[hash(_word)];

    // skip to return false for no linked list
    while (_node != NULL) {
        // check if _node points to correct word
        if (strcmp(_node->word, _word) == 0) {
            free(_word);
            return true;
        }
        // else increment to next node
        _node = _node->next;
    }
    free(_word);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int sum = 0;

    for (int i = 0; word[i] != '\0'; i++) {
        // add ASCII value of word[i] to sum
        sum += word[i];
    }
    return sum%(LENGTH+1);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict_file = fopen(dictionary, "r");

    // check for valid file
    if (dictionary != NULL) {
        char buffer[LENGTH+1];

        while(fscanf(dict_file, "%s", buffer) != EOF) {
            node *_node = malloc(sizeof(node));

            // check if memory was allocated
            if (_node != NULL) {
                strcpy(_node->word, buffer);

                // Set new pointer
                _node->next = table[hash(buffer)];
                // Set head to new pointer
                table[hash(buffer)] = _node;

                dict_size++;
            }
            else {
                fclose(dict_file);
                return false;
            }
        }
        fclose(dict_file);
        return true;
    }
    fclose(dict_file);
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for(int i = 0; i < N; i++) {
        node * _node = table[i];

        while(_node != NULL) {
            node *temp = _node;
            _node = _node->next;
            free(temp);
        }
    }
    return true;
}