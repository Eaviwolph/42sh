/*
** builtin_shopt.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Mar 22 16:27:35 2006 Seblu
** Last update Wed Nov 15 15:18:32 2006 seblu
*/

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../shell/option.h"
#include "../shell/shell.h"
#include "builtin.h"

/*
** ============
** DECLARATIONS
** ============
*/

/*!
** Retreinve command line option
**
** @param argv argument vector
** @param argp argument position
** @param line line flag
** @param ext extended flag
*/
static void getoption(char *argv[], int *argp, int opts[2]);

/*!
** Sun or unset an option
**
** @param argv arg vector
** @param argp cur pos
** @param opts argline opts
**
** @return builtin status
*/
static int mutator_opt(char *argv[], int *argp, int opts[2]);

/*!
** Show info about shell opts
**
** @param argv arg vector
** @param argp cur pos
** @param opts argline opts
**
** @return builtin status
*/
static int show_opt(char *argv[], int *argp, int opts[2]);

/*!
** Show all options
**
** @param quiet silent showing
**
** @return return status
*/
static int show_all_opt(int quiet);

/*
** ===========
** DEFINITIONS
** ===========
*/

int builtin_shopt(char *argv[])
{
    int argp = 1;
    int opts[2];
    // opts[0] == set or unset mode
    // opts[1] == quiet mode

    assert(argv && argv[0]);
    opts[0] = -1;
    opts[1] = 0;
    getoption(argv, &argp, opts);
    if (opts[0] == -1 && !argv[argp])
        return show_all_opt(opts[1]);
    else if (opts[0] == -1 && argv[argp])
        return show_opt(argv, &argp, opts);
    else
        return mutator_opt(argv, &argp, opts);
}

static void getoption(char *argv[], int *argp, int opts[2])
{
    for (; argv[*argp]; ++*argp)
        if (!strcmp("-s", argv[*argp]))
            opts[0] = 1;
        else if (!strcmp("-u", argv[*argp]))
            opts[0] = 0;
        else if (!strcmp("-q", argv[*argp]))
            opts[1] = 1;
        else
            break;
}

static int mutator_opt(char *argv[], int *argp, int opts[2])
{
    int ret = 0;

    for (; argv[*argp]; ++*argp)
    {
        if (option_is_set(shell->option, argv[*argp]) == -1)
        {
            fprintf(stderr, "%s: shopt: %s: invalid shell option name\n",
                    shell->name, argv[*argp]);
            ret = 1;
            continue;
        }
        if (opts[0])
            option_set(shell->option, argv[*argp]);
        else
            option_unset(shell->option, argv[*argp]);
    }
    return ret;
}

static int show_opt(char *argv[], int *argp, int opts[2])
{
    int ret = 0;
    int isset = 0;

    for (; argv[*argp]; ++*argp)
    {
        if ((isset = option_is_set(shell->option, argv[*argp])) == -1)
        {
            fprintf(stderr, "%s: shopt: %s: invalid shell option name\n",
                    shell->name, argv[*argp]);
            ret = 1;
            continue;
        }
        if (!opts[1])
            printf("%-15s %s\n", argv[*argp], (isset) ? "yes" : "no");
        else if (!isset)
            ret = 1;
    }
    return ret;
}

static int show_all_opt(int quiet)
{
    const char **opts;
    register int i;

    if (quiet)
        return 0;
    opts = opt_get();
    for (i = 0; opts[i]; ++i)
        printf("%-15s %s\n", opts[i],
               (option_is_set(shell->option, opts[i])) ? "yes" : "no");
    return 0;
}
