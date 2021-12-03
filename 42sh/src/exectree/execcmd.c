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

static int index_of(char *s, char c)
{
    for (int i = 0; s[i]; i++)
    {
        if(s[i] == c)
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
        dvar_add_var(s->var, prefix[i], prefix[i] + index + 1);
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