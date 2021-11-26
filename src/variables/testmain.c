#include <stdio.h>
#include <stdlib.h>
#include "var.h"

int main(void)
{
    char *names[] = { strdup("0"), strdup("1"), strdup("2"), strdup("3") };
    char *vars[] = { strdup("Je"), strdup("Suis"), strdup("Une"),
                     strdup("Variable") };
    struct dvar *d = initvars(names, vars, 4);
    dvar_add_var(d, strdup("Hello"), strdup("World"));
    dvar_add_var(d, strdup("Bonsoir"), strdup("Salut"));
    dvar_add_var(d, strdup("Holla"), strdup("BONYOUR"));
    dvar_add_var(d, strdup("Priviet"), strdup(""));
    dvar_print(d);
    printf("------------------\n");
    char *s = strdup("$#Hello");
    s = strrep(s, d);
    printf("s = %s\n", s);
    free(s);
    dvar_destroy(d);

    return 0;
}