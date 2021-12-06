#ifndef SHELL_H
#define SHELL_H

#include "../alias/alias.h"
#include "../functions/dfunc.h"
#include "../parser/dtoken.h"
#include "../tree/tree.h"
#include "../variables/var.h"

struct shell
{
    char *name;
    struct dvar *var;
    struct dalias *alias;
    struct dfunc *fun;
    struct dtoken *token;
    struct node *tree;
    int pretty_print;
};

#endif