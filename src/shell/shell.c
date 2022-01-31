#include "shell.h"

#include <ctype.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#include "../common/macro.h"
#include "../exectree/exectree.h"
#include "../parser/parser.h"
#include "../parser/token.h"
#include "../tools/tools.h"

void freeshell(struct shell *sh)
{
    if (sh->token)
        destroy_dtoken(sh->token);
    if (sh->var)
        dvar_destroy(sh->var);
    if (sh->alias)
        dalias_destroy(sh->alias);
    if (sh->fun)
        dfunc_destroy(sh->fun);
    free(sh);
}

static struct dvar *getvars(int len, char *args[], char *n)
{
    char **names = NULL;
    char **vars = NULL;
    if (len > 0)
    {
        names = calloc(len, sizeof(char *));
        vars = calloc(len, sizeof(char *));
    }
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
    if (len <= 0)
    {
        len++;
        names = calloc(len, sizeof(char *));
        vars = calloc(len, sizeof(char *));
        names[0] = mystrdup("0");
        vars[0] = mystrdup(n);
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
    srand(time(NULL) + (long)sh);
    if (argc >= 1)
    {
        sh->name = argv[0];
    }
    j = (argc >= 2 && (strcmp(argv[1], "--pretty-print") == 0));
    sh->pretty_print = j;
    argc -= (j ? 1 : 0);

    if (argc >= 2)
    {
        if (argc > 2 && strcmp(argv[j ? 2 : 1], "-c") == 0)
        {
            char quoted = '\0';
            sh->token = dtoken_init();
            sh->token = str_to_dtoken(sh->token, argv[j ? 3 : 2], &quoted);
            sh->token = dtoken_add(sh->token, calloc(1, sizeof(char)));
            sh->token->tail->data.op = LEOF;

            sh->var = getvars(argc - 3 + (j ? 1 : 0), argv + 3, argv[0]);
        }
        else
        {
            sh->var = getvars(argc - 1, argv + 1, argv[0]);
            fd = open(argv[j ? 2 : 1], O_RDONLY);
            if (fd == -1)
                errx(1, "%s: can't be open or doesn't exist", argv[j ? 2 : 1]);
            sh->token = readlines(fd);
        }
    }
    else
    {
        sh->var = getvars(argc + (j ? 1 : 0), argv, argv[0]);
        sh->token = readlines(fd);
    }
    sh->fun = dfunc_init();
    sh->alias = dalias_init();
    dalias_add_alias(sh->alias, mystrdup("$@"),
                     mystrdup(dvar_find(sh->var, "@")));

    struct dtoken_item *l = sh->token->head;
    while (l)
    {
        if (l->data.op == LWORD && l->next && is_prefix(l->next->data)
            && isdigit(l->data.val[0]))
        {
            l->data.op = LIONUMBER;
        }
        l = l->next;
    }
    do
    {
        sh->tree = parse(sh->token, sh->alias);
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
    } while (peak_token(sh->token, sh->alias).op != LEOF);
    freeshell(sh);
    return 0;
}
