#include <stdio.h>
#include <stdlib.h>

#include "alias.h"

static char *strdup(const char *s)
{
    size_t len = strlen(s) + 1;
    void *new = malloc(len);
    if (new == NULL)
        return NULL;
    return (char *)memcpy(new, s, len);
}

int main(void)
{
    struct dalias *d = dalias_init();
    dalias_add_alias(d, strdup("Hello"), strdup("World"));
    dalias_add_alias(d, strdup("Bonsoir"), strdup("Salut"));
    dalias_add_alias(d, strdup("Holla"), strdup("BONYOUR"));
    dalias_add_alias(d, strdup("Priviet"), strdup(""));
    dalias_add_alias(d, strdup("gccx"), strdup("gcc -Wall -Werror -Wextra -std=c99 -pedantic -g3 -fsanitize=address"));
    dalias_print(d);
    printf("------------------\n");
    char *s = strdup("*.c gccx");
    s = aliasstrrep(s, d);
    printf("s = %s\n", s);
    free(s);
    dalias_destroy(d);

    return 0;
}