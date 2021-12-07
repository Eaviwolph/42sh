#define _POSIX_SOURCE
#include <assert.h>
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../builtin/builtin.h"
#include "../tools/tools.h"
#include "exectree.h"

int decode_status(int status)
{
    if (WIFEXITED(status))
    {
        int rc = WEXITSTATUS(status);
        return rc;
    }
    int sig = WTERMSIG(status);
    return sig;
}

static int index_of(char *s, char c)
{
    for (int i = 0; s[i]; i++)
    {
        if (s[i] == c)
            return i;
    }
    return -1;
}

static void execprefix(char **prefix, struct shell *s)
{
    for (int i = 0; prefix[i]; ++i)
    {
        int index = index_of(prefix[i], '=');
        prefix[i][index] = '\0';
        dvar_add_var(s->var, mystrdup(prefix[i]),
                     mystrdup(prefix[i] + index + 1));
    }
}

void execfork(struct node_cmd n, struct shell *s, int size, char **ar)
{
    // forking
    int pid = fork();
    if (pid == -1)
    {
        errx(1, "fork error");
    }
    else if (pid == 0)
    {
        execvp(ar[0], ar);
        if (errno == ENOENT)
            fprintf(stderr, "%s: %s: command not found.\n", s->name, n.argv[0]);
        for (int i = 0; i < size; i++)
        {
            free(ar[i]);
        }
        free(ar);
        exit(EXIT_FAILURE);
    }
    int status;
    int r = waitpid(pid, &status, 0);
    if (r == -1)
        errx(1, "waitpid");

    char *temp = calloc(12, sizeof(char));
    temp = myitoa(decode_status(status), temp);
    dvar_add_var(s->var, mystrdup("?"), temp);
}

void execargv(struct node_cmd n, struct shell *s)
{
    int size = n.sizea;
    char **ar = malloc(sizeof(char *) * (size + 1));
    for (int i = 0; i < size; i++)
    {
        ar[i] = varstrrep(mystrdup(n.argv[i]), s->var);
        if (!ar[i])
            errx(1, "Parsing Error");
    }
    ar[size] = NULL;

    if (!strcmp(ar[0], "echo"))
    {
        my_echo(ar, size);
        fflush(stdout);
    }
    else if (!strcmp(ar[0], "break"))
    {
        dvar_add_var(s->var, mystrdup("loop_status"), mystrdup("break"));
    }
    else if (!strcmp(ar[0], "continue"))
    {
        dvar_add_var(s->var, mystrdup("loop_status"), mystrdup("continue"));
    }
    else
    {
        execfork(n, s, size, ar);
    }

    for (int i = 0; i < size; i++)
    {
        free(ar[i]);
    }
    free(ar);
}

void execcmd(struct node_cmd n, struct shell *s)
{
    if (n.sizep)
        execprefix(n.pref, /*1,*/ s);
    if (n.sizea && !execfunc(n, s))
    {
        execargv(n, s);
    }
}
