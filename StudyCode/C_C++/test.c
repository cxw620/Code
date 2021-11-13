#include <stdio.h>
int main(void)
{
    int count, mid, asciiLetter;
    for (count = 1; count <= 26; ++count)
    {
        asciiLetter = 65;
        for (mid = 1; mid <= 51; ++mid)
        {
            if (mid > 26 - count && mid < 26 + count)
            {
                if (mid < 27)
                {
                    printf("%c", asciiLetter);
                    if (mid == 26)
                    {
                        continue;
                    }
                    ++asciiLetter;
                }
                else
                {
                    printf("%c", --asciiLetter);
                }
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}