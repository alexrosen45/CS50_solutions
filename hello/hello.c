#include <stdio.h>
#include <cs50.h> /* import custom cs50 functions */

int main(void)
{
    string name = get_string("Enter your name, please: "); /* get user inp */
    printf("Hello, %s\n", name);
}