#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void) {
    string text = get_string("Enter text: ");
    int words = 1; // assume one word at least
    int sentences = 0;
    int letters = 0;

    for (int i=0; i<strlen(text); i++) {
        // check for blank space
        if (text[i] == 32) {
            words++;
        }
        // check for sentence ending chars
        else if (text[i] == 33 || text[i] == 46 || text[i] == 63) {
            sentences++;
        }
        // check for letters
        else if (tolower(text[i]) > 96 && tolower(text[i]) < 123) {
            letters++;
        }
    }

    // determine index
    int readability = round(0.0588*(letters*100)/words-0.296*(sentences*100)/words-15.8);

    if (readability > 16) {
        printf("Grade 16+\n");
    }
    else if (readability < 1) {
        printf("Before Grade 1\n");
    }
    else {
        printf("Grade %i\n", readability);
    }
}