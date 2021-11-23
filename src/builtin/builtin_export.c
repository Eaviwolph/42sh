/*
** builtin_export.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Thu May 11 09:32:30 2006 Seblu
** Last update Fri Nov 17 12:57:12 2006 seblu
*/

#include <assert.h>
#include <stdio.h>

#include "../shell/shell.h"

int builtin_export(char *argv[])
{
    assert(argv);
    fprintf(stderr, "%s: export: not yet implemeted.\n", shell->name);
    (void)argv;
    return 1;
}
