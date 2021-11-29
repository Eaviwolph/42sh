#include "shell.h"

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../parser/token.h"
#include "../parser/parser.h"
#include "../common/macro.h"

void freeshell(struct shell *sh)
{
    destroy_dtoken(sh->token);
    tree_destroy(sh->tree);
    free(sh);
}

int main(int argc, char *argv[])
{
    int fd = 0;
    struct shell *sh;
    safe_calloc(sh, 1, sizeof(struct shell));
    if (argc <= 2)
    {
        if (argc == 2)
        {
            fd = open(argv[1], O_RDONLY);
            if (fd == -1)
                errx(1, "%s: can't be open or doesn't exist", argv[1]);
        }
        sh->token = readlines(fd);
    }
    else
    {
        if (strcmp(argv[1], "-e") != 0)
            errx(1, "%s: invalid parameters", argv[1]);
        char quoted = '\0';
        sh->token = dtoken_init();
        sh->token = str_to_dtoken(sh->token, argv[2], &quoted);
    }
    print_dtoken(sh->token);
    sh->tree = parse(sh->token);
    tree_print_node(sh->tree, stdout);
    freeshell(sh);
    return 0;
}
