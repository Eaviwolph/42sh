#include <stdio.h>
#include <stdlib.h>
#include "alias.h"

int main(void)
{
    char *names[] = { strdup("0"), strdup("1"), strdup("2"), strdup("3") };
    char *vars[] = { strdup("Je"), strdup("Suis"), strdup("Une"),
                     strdup("Variable") };
    struct dalias *d = initvars(names, vars, 4);
    dalias_add_var(d, strdup("Hello"), strdup("World"));
    dalias_add_var(d, strdup("Bonsoir"), strdup("Salut"));
    dalias_add_var(d, strdup("Holla"), strdup("BONYOUR"));
    dalias_add_var(d, strdup("Priviet"), strdup(""));
    dalias_print(d);
    printf("------------------\n");
    char *s = strdup("$#Hello");
    s = strrep(s, d);
    printf("s = %s\n", s);
    free(s);
    dalias_destroy(d);

    return 0;
}