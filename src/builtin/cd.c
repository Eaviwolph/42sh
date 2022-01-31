#define _DEFAULT_SOURCE

#include "builtin.h"

int exists(char *name)
{
    struct stat file_stat;
    if (stat(name, &file_stat) < 0)
        return 0;
    return 1;
}

int my_cd(char *arg[], size_t len)
{
    if (len == 0)
        chdir("/home");
    else if (len != 1)
        errx(1, "cd: too many arguments");
    else if (exists(arg[0]))
    {
        chdir(arg[0]);
        char *tmp;
        if ((tmp = getenv("PWD")))
            setenv("OLDPWD", tmp, !0);
        tmp = getcwd(tmp, PATH_MAX * sizeof(char));
        setenv("PWD", tmp, !0);
    }
    else
        errx(1, "cd: %s: No such file or directory", arg[0]);
    return 0;
}