#ifndef VAR_H
#define VAR_H

#include "dvar.h"

char *varstrrep(char *s, struct dvar *var);
struct dvar *initvars(char **names, char **vars, int size);
char *strdup(const char *s);

#endif