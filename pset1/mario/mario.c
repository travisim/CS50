#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

int main(void)
{
    int height;
    bool n;
    do
    {
        height = get_int("Height: ");

    }
    /*while ( height < 0 || height > 8 || isalpha(height));*/
    while ((0 < height && height < 9) == !true);
    int empty = 0;
    int hash = 1;
    empty = height - 1;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < empty; j++)
        {
            printf(" ");
        }
        for (int k = 0; k < hash; k++)
        {
            printf("#");
        }
        hash++;
        empty--;
        printf("\n");
    }
}

