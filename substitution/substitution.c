#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[]){
    char characters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char key[26];

    // error for incorrect number of arguments
    if (argc != 2){
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // counter to check for 26 unique letters
    int counter = 0;

    // check for 26 unique letters
    if (strlen(argv[1]) == 26) {
        for (int i=0; i<26; i++) {
            for (int j=0; j<26; j++) {
                if (tolower(argv[1][i]) == characters[j]) {
                    key[i] = tolower(argv[1][i]);
                    counter++;
                    characters[j] = '0';
                }
            }
        }
    }
    else {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // stop program if there are not 26 unique letters
    if (counter!=26) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    string plaintext = get_string("plaintext: ");

    for (int i=0; i<strlen(plaintext); i++) {
        // get dec value for char i in plaintext
        int val = tolower(plaintext[i]);

        // preserve capitalized vals
        bool cap = false;
        if (val != plaintext[i]) {
            cap = true;
        }

        if (val > 96 && val < 123) {
            // substract 97 such that val indexes key from 0
            char substituted_val = key[val-97];

            if (cap) {
                plaintext[i] = toupper(substituted_val);
            }
            else {
                plaintext[i] = substituted_val;
            }
        }
    }
    printf("ciphertext: %s\n", plaintext);
    return 0;
}