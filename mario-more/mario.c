#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    int arr[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    bool in_arr = false;

    do {
        in_arr = false;
        n = get_int("Enter height: ");

        // check if n in arr
        for (int i=0; i<8; i++) {
            if (n==arr[i]) {
                in_arr = true;
                break;
            }
        }
        // build wall
        if (in_arr) {
            int count = 1;
            char wall[n][n*2+1];

            for (int i=0; i<n; i++) {
                for (int j=0; j<n*2+1; j++) {
                    if (j<n-count) {
                        wall[i][j] = ' ';
                    }
                    else if (j>n+count) {
                        wall[i][j] = '0';
                    }
                    else if (j==n) {
                        wall[i][j] = 'm';
                    }
                    else {
                        wall[i][j] = '#';
                    }
                    if (wall[i][j] == 'm') {
                        printf("  ");
                    }
                    else if (wall[i][j] != '0') {
                        printf("%c", wall[i][j]);
                    }
                }
                count++;
                printf("\n");
            }

        }
        // throw error
        else {
            printf("ERROR: Invalid Input\n");
        }
    } while (n<1 || n>8);
}