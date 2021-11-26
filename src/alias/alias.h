#ifndef VAR_H
#define VAR_H

#include "dalias.h"

char *strrep(char *s, struct dalias *var);
struct dalias *initvars(char **names, char **vars, int size);
char *strdup(const char *s);

#endif