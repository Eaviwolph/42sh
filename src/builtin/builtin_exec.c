/*
** builtin_exec.c for 42sh in /goinfre/seblu/42sh/src/builtin
**
** Made by Seblu
** Login   <luttri_s@epita.fr>
**
** Started on  Thu May 11 10:00:36 2006 Seblu
** Last update Fri Nov 17 13:01:59 2006 seblu
*/

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../shell/shell.h"

int builtin_exec(char *argv[])
{
    assert(argv);
    if (!argv[1])
        return 0;
    if (execvp(argv[1], argv + 1) == -1)
    {
        fprintf(stderr, "%s: exec: %s.\n", shell->name, strerror(errno));
        return 127;
    }
    return 0;
}
