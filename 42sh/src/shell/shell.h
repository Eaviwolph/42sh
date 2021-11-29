#ifndef SHELL_H
#define SHELL_H

#include "../alias/alias.h"
#include "../parser/dtoken.h"
#include "../variables/var.h"

struct shell
{
    struct dvar *var;
    struct dalias *alias;
    struct dtoken *token;
};

#endif