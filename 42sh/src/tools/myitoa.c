#include <stdlib.h>

char *myitoa(int value, char *s)
{
    if (value == 0)
    {
        s[0] = '0';
        s[1] = '\0';
    }
    else
    {
        size_t i = 0;
        if (value < 0)
        {
            s[0] = '-';
            value = -value;
            i++;
        }
        size_t cp = value;
        while (cp > 0)
        {
            cp /= 10;
            i++;
        }
        s[i] = '\0';
        i--;
        while (value > 0)
        {
            s[i] = '0' + (value % 10);
            i--;
            value /= 10;
        }
    }
    return s;
}
