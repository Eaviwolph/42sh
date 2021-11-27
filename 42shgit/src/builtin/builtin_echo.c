/*
** builtin_echo.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Tue Mar 14 20:57:07 2006 Seblu
** Last update Wed Nov 15 15:34:18 2006 seblu
*/

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../shell/option.h"
#include "../shell/shell.h"

/*
** ======
** MACROS
** ======
*/

#define isoctale(x) (((x) >= '0' && (x) <= '7') ? 1 : 0)

/*
** ============
** DECLARATIONS
** ============
*/

/*!
** Retreive command line option
**
** @param argv argument vector
** @param argp argument position
** @param line line flag
** @param ext extended flag
*/
static void getoption(char *argv[], int *argp, int *line, int *ext);

/*!
**
**
** @param msg
**
** @return if return 0, builtin must quit immediatly, else ok.
*/
static int builtin_echo_ext(const char *msg);

/*!
** Print hexa number on stdout a number
**
** @param msg message to print
** @param base base of the number
*/
static void print_hex(const char **);

/*!
** Print oct number on stdout a number
**
** @param msg message to print
** @param base base of the number
*/
static void print_oct(const char **);

/*!
** Function to say if c is a digit or not.
** It use macro isdigit, but due to epita coding style
** restriction about cast, it's impossible to call
** a macro wrote with int with char, because cast is forbidden
** and macro call, dont have the same right about parameter
** implicit cast (on netBSD)
**
** @param c character
**
** @return if \param c is a digit
*/
static int fisdigit(const int c);

/*!
** Function to say if c is a digit or not.
** It use macro isdigit, but due to epita coding style
** restriction about cast, it's impossible to call
** a macro wrote with int with char, because cast is forbidden
** and macro call, dont have the same right about parameter
** implicit cast (on netBSD)
**
** @param c character
**
** @return if \param c is a hexa digit
*/
static int fisxdigit(const int c);

/*
** ===========
** DEFINITIONS
** ===========
*/

int builtin_echo(char *argv[])
{
    int argp;
    int ext = 0;
    int line = 1;
    int first;

    assert(argv && argv[0]);
    ext = option_is_set(shell->option, "xpg_echo");
    for (getoption(argv, &argp, &line, &ext), first = argp; argv[argp]; ++argp)
    {
        if (first != argp)
            printf(" ");
        if (ext && !builtin_echo_ext(argv[argp]))
            return fflush(stdout);
        printf("%s", argv[argp]);
    }
    if (line)
        printf("\n");
    return fflush(stdout);
}

static void getoption(char *argv[], int *argp, int *line, int *ext)
{
    char *carg;

    for (*argp = 1; (carg = argv[*argp]); ++*argp)
        if (*carg == '-')
            for (++carg; *carg; ++carg)
                if (*carg == 'e')
                    *ext = 1;
                else if (*carg == 'E')
                    *ext = 0;
                else if (*carg == 'n')
                    *line = 0;
                else
                    return;
        else
            return;
}

static int builtin_echo_ext(const char *msg)
{
    int backed = 0;

    for (; *msg; ++msg)
        if (*msg == '\\' && !backed && (backed = 1))
            continue;
        else if (backed && *msg == 'a' && !(backed = 0))
            putchar('\a');
        else if (backed && *msg == 'b' && !(backed = 0))
            putchar('\b');
        else if (backed && *msg == 'c')
            return 0;
        else if (backed && *msg == 'e' && !(backed = 0))
            putchar(0x1b);
        else if (backed && *msg == 'f' && !(backed = 0))
            putchar('\f');
        else if (backed && *msg == 'n' && !(backed = 0))
            putchar('\n');
        else if (backed && *msg == 'r' && !(backed = 0))
            putchar('\r');
        else if (backed && *msg == 't' && !(backed = 0))
            putchar('\t');
        else if (backed && *msg == '\\' && !(backed = 0))
            putchar('\\');
        else if (backed && *msg == 'v' && !(backed = 0))
            putchar('\v');
        else if (backed && fisdigit(*msg) && !(backed = 0))
            print_oct(&msg);
        else if (backed && *msg == 'x' && !(backed = 0) && (++msg))
            print_hex(&msg);
        else if (backed && !(backed = 0))
            printf("\\%c", *msg);
        else
            putchar(*msg);
    return 1;
}

static void print_hex(const char **msg)
{
    char buf[4];
    char *end;
    long n;
    unsigned char c;
    int i;

    if (!fisxdigit(**msg))
        return;
    for (i = 0; fisxdigit(**msg) && i < 2; ++*msg, ++i)
        buf[i] = **msg;
    buf[i] = 0;
    --*msg;
    n = strtoul(buf, &end, 16);
    printf("%c", (c = n));
}

static void print_oct(const char **msg)
{
    char buf[5];
    char *end;
    unsigned long n;
    unsigned char c;
    int i;
    int max;

    if (!isoctale(**msg))
        return;
    max = (**msg == '0') ? 4 : 3;
    for (i = 0; isoctale(**msg) && i < max; ++*msg, ++i)
        buf[i] = **msg;
    buf[i] = 0;
    --*msg;
    n = strtoul(buf, &end, 8);
    printf("%c", (c = n));
}

static int fisdigit(const int c)
{
    return isdigit(c);
}

static int fisxdigit(const int c)
{
    return isxdigit(c);
}
