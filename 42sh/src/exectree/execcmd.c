#define _GNU_SOURCE
#include <assert.h>
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

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

static void execprefix(char **prefix,/* int glob,*/ struct shell *s)
{
    char *value;
    for (int i = 0; prefix[i]; ++i)
    {
        if (!(value = strchr(prefix[i], '=')))
            assert(0);
        *value = 0;
        /*if (glob || getenv(prefix[i]) != NULL)
            senv2(prefix[i], value + 1, !0);*/
        // else
        dvar_add_var(s->var, prefix[i], value + 1);
        *value = '=';
    }
}

void execargv(struct node_cmd n, struct shell *s)
{
    int pid = fork();
    if (pid == -1)
    {
        errx(1, "fork error");
    }
    else if (pid == 0)
    {
        int size = 0;
        if (n.argv)
        {
            while (n.argv[size])
                ++size;
        }
        char **ar = malloc(sizeof(char *) * (size + 1));
        for (int i = 0; i < size; i++)
        {
            ar[i] = varstrrep(strdup(n.argv[i]), s->var);
            if (!ar[i])
                errx(1, "Parsing Error");
        }
        ar[size] = NULL;

        execvp(ar[0], ar);
        if (errno == ENOENT)
            fprintf(stderr, "%s: %s: command not found.\n", s->name, n.argv[0]);
        else
            perror(s->name);
        for (int i = 0; i < size; i++)
        {
            free(ar[i]);
        }
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

void execcmd(struct node_cmd n, struct shell *s)
{
    if (n.pref)
        execprefix(n.pref, /*1,*/ s);
    if (n.argv)
        execargv(n, s);
}