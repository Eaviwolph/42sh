#ifndef FUNCTION_H
#define FUNCTION_H

#include <stddef.h>

int str_isnumber(const char *str);

char *str_array_concat(char **vtable);

char *end_path_name(const char *path);

char *str_concat(const char *s1, const char *s2);

char *cwd_string(void);

char **string_array_append(char **vector, char *str);

int add_env_var(char *varname, char *varvalue, int overwrite);

int del_env_var(const char *varname);

#endif