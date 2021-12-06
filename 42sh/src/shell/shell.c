#include "shell.h"

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../common/macro.h"
#include "../exectree/exectree.h"
#include "../parser/parser.h"
#include "../parser/token.h"

// void faketree(struct shell *s);

void freeshell(struct shell *sh)
{
    if (sh->token)
        destroy_dtoken(sh->token);
    if (sh->var)
        dvar_destroy(sh->var);
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
    int j = 0;
    struct shell *sh;
    safe_calloc(sh, 1, sizeof(struct shell));
    if (argc >= 1)
    {
        sh->name = argv[0];
    }
    if (argc >= 2)
    {
        j = (strcmp(argv[1], "--pretty-print") == 0);
        if (argc > 2 && strcmp(argv[1], "-c") == 0)
        {
            char quoted = '\0';
            sh->token = dtoken_init();
            sh->token = str_to_dtoken(sh->token, argv[2], &quoted);
            sh->token = dtoken_add(sh->token, calloc(1, sizeof(char)));
            sh->token->tail->data.op = LEOF;

            sh->var = getvars(argc - 3, argv + 3);
        }
        else
        {
            if (j)
            {
                sh->pretty_print = 1;
            }
            sh->var = getvars(argc - 1, argv + 1);
            fd = open(argv[j ? 2 : 1], O_RDONLY);
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
    do
    {
        sh->tree = parse(sh->token);
        if (sh->tree)
        {
            if (sh->pretty_print)
            {
                tree_print_node(sh->tree, stdout);
                printf("\n");
            }
            exectree(sh->tree, sh);
        }
        tree_destroy(sh->tree);
    } while (peak_token(sh->token).op != LEOF);
    freeshell(sh);
    return 0;
}
