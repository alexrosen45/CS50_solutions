#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    string type = "INVALID"; // card type
    bool valid = false;
    bool master = false;
    bool visa = false;
    bool amex = false;
    const int MASTERCARD[5] = {51, 52, 53, 54, 55}; // MasterCard prefixes
    const int AMEX[2] = {34, 37}; // American Express prefixes
    const int VISA = 4; // Visa prefix

    long inp = get_long("Enter card number: "); // get user card number
    long digit = inp;
    long digits = inp;

    // check for Visa
  	while(digit >= 10) {
  		digit /= 10;
  	}

    if (digit == VISA) {
        type = "VISA";
        valid = true;
        visa = true;
    }
    // check for American Express and MasterCard
    else {
        while(digits >= 100) { digits /= 10; }

        for (int i=0; i<5; i++) {
            if (digits == MASTERCARD[i]) {
                type = "MASTERCARD";
                valid = true;
                master = true;
            }
        }

        for (int i=0; i<2; i++) {
            if (digits == AMEX[i]) {
                type = "AMEX";
                valid = true;
                amex = true;
            }
        }
    }
    // throw invalid card
    if (valid == false) {
        printf("INVALID\n");
    }
    // continue for valid card
    else {
        // get length of long
        int len = 1;
        long temp = inp;

        while (temp>9) {
            len++;
            temp/=10;
        }

        int arr[len];
        int checksum = 0;
        temp = inp;

        // turn long into reversed array
        for (int i = 0; i < len; i++) {
            arr[i] = temp % 10;
            temp /= 10;
        }

        // preform checksum through reversed array
        for (int i = 0; i < len; i++) {
            // for even indexes
            if (i%2 == 0) {
                checksum += arr[i];
            }
            // for odd indexes
            else {
                // split into digits
                if (arr[i]*2 > 9) {
                    checksum += 1+((arr[i]*2)%10);
                }
                else {
                    checksum += arr[i]*2;
                }
            }
        }

        // output valid card type
        if (checksum%10 == 0) {
            if (visa) {
                if (len == 13 || len == 16) {
                    printf("%s\n", type);
                }
                // throw invalid card
                else {
                    printf("INVALID\n");
                }
            }
            else if (master && len == 16) {
                printf("%s\n", type);
            }
            else if (amex && len == 15) {
                printf("%s\n", type);
            }
            // throw invalid card
            else {
                printf("INVALID\n");
            }
        }
        // throw invalid card
        else {
            printf("INVALID\n");
        }
    }
}