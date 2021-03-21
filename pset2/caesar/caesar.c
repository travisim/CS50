#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    int check_int = 1;
    if (argc == 2)
    {
        check_int = 1;
        for (int i = 0, len = strlen(argv[1]); i < len; i++)
        {
            if isalpha(argv[1][i])
            {
                check_int = 1;
                break;
            }
            else
            {

            }
            check_int = 0;
        }
        if (check_int == 0)
        {
            int key = atoi(argv[1]);
            string text = get_string("plaintext: ");
            for (int i = 0, n = strlen(text); i < n; i++)
            {

                if (text[i] >= 65 && text[i] <= 90)
                {
                    text [i] = (text[i] + key - 65) % 26 + 65;
                }
                else if (text[i] >= 97 && text[i] <= 121)
                {
                    text [i] = (text[i] + key - 97) % 26 + 97;
                }
                else
                {

                }
            }
            printf("ciphertext: %s\n", text);

        }
        else
        {
            printf("Usage: ./caesar key\n");

        }

    }
    else
    {


    }
    return check_int;
}