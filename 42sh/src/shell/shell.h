#ifndef SHELL_H
#define SHELL_H

#include "../alias/alias.h"
#include "../parser/dtoken.h"
#include "../variables/var.h"
#include "../tree/tree.h"

struct shell
{
    char *name;
    struct dvar *var;
    struct dalias *alias;
    struct dtoken *token;
    struct node *tree;
    int pretty_print;
};

#endif