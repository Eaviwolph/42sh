#define _XOPEN_SOURCE
#define _DEFAULT_SOURCE

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "function.h"
#include "macro.h"

char *str_concat(const char *s1, const char *s2)
{
    char *r;
    safe_malloc(r, strlen(s1) + strlen(s2) + 1);
    strcat(strcat(r, s1), s2);
    return r;
}

char *str_array_concat(char **vtable)
{
    if (!vtable)
        return NULL;
    int len = 0;
    for (int i = 0; vtable[i]; i++)
    {
        len += strlen(vtable[i]);
    }
    char *r;
    safe_malloc(r, len + 1);
    strcpy(r, "");
    for (int j = 0; vtable[j]; j++)
    {
        strcat(r, vtable[j]);
    }
    return r;
}

static char *substring(const char *name_path, int begin, int end)
{
    return strndup(name_path + begin, (begin > end) ? 0 : end - begin + 1);
}

static int find_slash(const char *name_path, int *i, int start)
{
    for (*i = start;; --i)
    {
        if (name_path[*i] != '/')
            return 0;
        if (*i == 0)
            return 1;
    }
    return -1;
}

char *end_path_name(const char *name_path)
{
    int begin = 0;
    int end = 0;
    int length = strlen(name_path);
    int i;
    if (length == 0)
        return strdup("");

    int r = find_slash(name_path, &i, length - 1);
    if (!r)
        end = i;
    if (end == 0)
        return strdup("");

    r = find_slash(name_path, &i, end - 1);
    if (!r)
        begin = i + 1;
    return substring(name_path, begin, end);
}

int str_isnumber(const char *s)
{
    if (s[0] == '\0')
        return 0;
    int r = 1;
    for (int i = 0; s[i]; i++)
        r &= ('0' <= s[i] && s[i] <= '9');
    return r;
}

char **string_array_append(char **arr, char *toappend)
{
    if (!toappend)
        return arr;
    int start = 0;

    if (arr) // skip to end
    {
        for (start = 0; arr[start]; ++start)
            continue;
    }
    start++;
    safe_realloc(arr, arr, (start + 1) * sizeof(char *));
    arr[start - 1] = toappend;
    arr[start] = NULL;
    return arr;
}

char *cwd_string(void)
{
    char *temp;
    safe_malloc(temp, 4096); // sizeofchar * PATHMAX but it's 1 on most os
    return getcwd(temp, 4096);
}

int add_env_var(char *varname, char *varvalue, int overwrite)
{
    extern char **environ;
    char **env = environ;
    assert(varname && varvalue && env);

    if (!overwrite)
    {
        int length = strlen(varname);
        for (; *env; ++env)
            if (!strncmp(varname, *env, length) && (*env)[length] == '=')
                return 1;
    }
    char *buf;
    safe_malloc(buf, strlen(varname) + 2 + strlen(varvalue));
    buf = strcat("", varname);
    buf = strcat(buf, "=");
    buf = strcat(buf, varvalue);
    return !putenv(buf) ? 0 : 2;
}

int del_env_var(const char *varname)
{
    if (!varname || varname[0] == '\0' || strchr(varname, '=') != NULL)
        return -1;
    extern char **environ;
    size_t len;
    char **env = environ;
    char **env2 = env;

    len = strlen(varname);
    for (int j = 0; env[j]; j++)
    {
        if (!strncmp(env[j], varname, len) && env[j][len] == '=')
        {
            env2 = env;
            do
                env2[0] = env2[1];
            while (++env2, *env2);
        }
    }
    return 0;
}
