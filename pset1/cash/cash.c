#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
string word = "hPPPk";
for (int i = 0, len = strlen(word); i < len; i++ )
    {
        word[i]=toupper(word[i]);
    }
//
}
/*int main(void)
{
    float change;
    do
    {
        change = get_float("Change owed: ");
        
    }
    while (change > 0 == !true);
    int cents;
    cents = round(change * 100);
    int counter = 0;
    while (cents != 0)
    {
        if (cents >= 25)
        {
            cents = cents - 25;
            counter++;
        }
        else if (cents >= 10)
        {
            cents = cents - 10;
            counter++;
        }
        else if (cents >= 5)
        {
            cents = cents - 5;
            counter++;
        }
        else if (cents >= 1)
        {
            cents = cents - 1;
            counter++;
        }
        
    }
    printf("%i\n", counter);
}

*/