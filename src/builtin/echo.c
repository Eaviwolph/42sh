#include "builtin.h"

size_t get_opt(size_t *n, size_t *e, char *arg[], size_t len)
{
    size_t i = 1;
    while (i < len && arg[i][0] == '-')
    {
        if (strcmp(arg[i], "-e") == 0)
            *e = 1;
        else if (strcmp(arg[i], "-n") == 0)
            *n = 0;
        else if (strcmp(arg[i], "-E") == 0)
            *e = 0;
        else if (strcmp(arg[i], "-ne") == 0 || strcmp(arg[i], "-en") == 0)
        {
            *n = 0;
            *e = 1;
        }
        else if (strcmp(arg[i], "-nE") == 0 || strcmp(arg[i], "-En") == 0)
        {
            *n = 0;
            *e = 0;
        }
        else
        {
            return i;
        }
        i++;
    }
    return i;
}

int is_octale(char c)
{
    return (c >= '0' && c <= '7') ? 1 : 0;
}

void octal(char **s)
{
    char buf[5];
    size_t i = 0;
    char *end;

    for (; i < 4 && is_octale(**s); i++, ++*s)
        buf[i] = **s;

    --*s;
    buf[i] = '\0';
    unsigned long x = strtoul(buf, &end, 8);
    char c = x;
    printf("%c", c);
}

void hexa(char **s)
{
    char buf[4];
    size_t i = 0;
    char *end;

    for (; i < 3 && isxdigit(**s); i++, ++*s)
        buf[i] = **s;

    --*s;
    buf[i] = '\0';
    unsigned long x = strtoul(buf, &end, 16);
    char c = x;
    printf("%c", c);
}

char special_char(char c)
{
    switch (c)
    {
    case 'a':
        return '\a';
    case 'b':
        return '\b';
    case 'f':
        return '\f';
    case 'n':
        return '\n';
    case 'r':
        return '\r';
    case 't':
        return '\t';
    case 'v':
        return '\v';
    default:
        return 0;
    }
}

void e_treat(char *s)
{
    int back = 0;
    char *str = s;
    char c;

    for (; *str; str++)
    {
        if (*str == '\\' && !back && (back = 1))
            str++;
        if (back && *str == 'c')
            return;
        else if (back && *str == 'e' && !(back = 0))
            putchar(0x1b);
        else if (back && *str == '0' && !(back = 0) && (str++))
            octal(&str);
        else if (back && *str == 'x' && !(back = 0) && (str++))
            hexa(&str);
        else if (back && (c = special_char(*str)) && !(back = 0))
            putchar(c);
        else if (back && !(back = 0))
            printf("\\%c", *str);
        else
            putchar(*str);
    }
}

int my_echo(char *arg[], size_t len)
{
    size_t n = 1;
    size_t e = 0;
    size_t first = get_opt(&n, &e, arg, len);
    for (size_t i = first; i < len; i++)
    {
        if (strlen(arg[i]))
        {
            if (!e)
                printf("%s", arg[i]);
            else
                e_treat(arg[i]);
            if (i + 1 < len)
            {
                printf(" ");
            }
        }
    }
    if (n)
        putchar('\n');
    return 0;
}