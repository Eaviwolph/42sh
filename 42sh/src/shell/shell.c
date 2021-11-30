#include "shell.h"

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../common/macro.h"
#include "../parser/parser.h"
#include "../parser/token.h"

void freeshell(struct shell *sh)
{
    if (sh->token)
        destroy_dtoken(sh->token);
    if (sh->var)
        dvar_destroy(sh->var);
    // if (sh->tree)
    // tree_destroy(sh->tree);
    if (sh->alias)
        dalias_destroy(sh->alias);
    free(sh);
}

struct dvar *getvars(int len, char *args[])
{
    char **names = calloc(len, sizeof(char *));
    char **vars = calloc(len, sizeof(char *));
    for (int i = 0; i < len; i++)
    {
        names[i] = calloc(11, sizeof(char));
        vars[i] = calloc(strlen(args[i]) + 1, sizeof(char));
        int j = 0;
        while (args[i][j])
        {
            vars[i][j] = args[i][j];
            j++;
        }
        snprintf(names[i], 10, "%d", i);
    }
    struct dvar *d = initvars(names, vars, len);
    free(names);
    free(vars);
    return d;
}

int main(int argc, char *argv[])
{
    int fd = 0;
    struct shell *sh;
    safe_calloc(sh, 1, sizeof(struct shell));
    if (argc >= 2)
    {
        if (argc > 2 && strcmp(argv[1], "-c") == 0)
        {
            char quoted = '\0';
            sh->token = dtoken_init();
            sh->token = str_to_dtoken(sh->token, argv[2], &quoted);
            sh->var = getvars(argc - 3, argv + 3);
        }
        else
        {
            sh->var = getvars(argc - 1, argv + 1);
            fd = open(argv[1], O_RDONLY);
            if (fd == -1)
                errx(1, "%s: can't be open or doesn't exist", argv[1]);
            sh->token = readlines(fd);
        }
    }
    else
    {
        sh->var = getvars(argc, argv);
        sh->token = readlines(fd);
    }
    dvar_print(sh->var);
    print_dtoken(sh->token);
    // sh->tree = parse(sh->token);
    // tree_print_node(sh->tree, stdout);
    freeshell(sh);
    return 0;
}
