#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

float index(int letters, int sentence, int words);
int main(void)
{

    string text = get_string("text: ");

    int letters = 0;
    int words = 0;
    int sentence = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        // counts the letters using ascii code
        if (text[i] >= 65 && text[i] <= 122)
        {
            letters++;
        }
        // counts the words by reading spaces
        else if (text[i] == 32/* */ && (text[i - 1] != 46/*.*/ && text[i - 1] != 33/*! */ && text[i - 1] != 63/*?*/))
        {
            words++;
        }
        // counts the sentences by finding dots, exclamation marks and interrogatives
        else if (text[i] == 63 || text[i] == 33 || text[i] == 46)
        {
            sentence++;
            words++;
        }
    }
    float value = index(letters, sentence, words);

    if (value < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (value >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int)round(value));
    }
}

float index(int letters, int sentence, int words)
{
    float L = (float)letters * 100 / (float)words;
    float S = (float)sentence * 100 / (float)words;
    float value = 0.0588 * L - 0.296 * S - 15.8;

    return value;
}
