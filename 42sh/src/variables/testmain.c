#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "var.h"
/*
int main(void)
{
    srand(time(NULL));
    char *names[] = { strdup("0"), strdup("1"), strdup("2"), strdup("3") };
    char *vars[] = { strdup("Je"), strdup("Suis"), strdup("Une"),
                     strdup("Variable") };
    struct dvar *d = initvars(names, vars, 4);
    dvar_add_var(d, strdup("Hello"), strdup("World"));
    dvar_add_var(d, strdup("Bonsoir"), strdup("Salut"));
    dvar_add_var(d, strdup("Holla"), strdup("BONYOUR"));
    dvar_add_var(d, strdup("Priviet"), strdup(""));
    char *s = strdup("$RANDOM$Hello$RANDOM");
    s = varstrrep(s, d);
    printf("s = %s\n", s);
    free(s);
    dvar_destroy(d);

    return 0;
}*/