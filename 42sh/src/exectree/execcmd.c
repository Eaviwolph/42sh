#define _GNU_SOURCE
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "exectree.h"

int decode_status(int status, struct shell *s, char *name)
{
    if (WIFEXITED(status))
    {
        int rc = WEXITSTATUS(status);
        return rc;
    }
    int sig = WTERMSIG(status);
    fprintf(stderr, "%s: %s: not found", s->name, name);
    return sig;
}

static char *mstrdup(const char *s)
{
    size_t len = strlen(s) + 1;
    void *new = malloc(len);
    if (new == NULL)
        return NULL;
    return (char *)memcpy(new, s, len);
}

static char *my_itoa(int value, char *s)
{
    if (value == 0)
    {
        s[0] = '0';
        s[1] = '\0';
    }
    else
    {
        size_t i = 0;
        if (value < 0)
        {
            s[0] = '-';
            value = -value;
            i++;
        }
        size_t cp = value;
        while (cp > 0)
        {
            cp /= 10;
            i++;
        }
        s[i] = '\0';
        i--;
        while (value > 0)
        {
            s[i] = '0' + (value % 10);
            i--;
            value /= 10;
        }
    }
    return s;
}

void execcmd(struct node_cmd *n, struct shell *s)
{
    int pid = fork();
    if (pid == -1)
    {
        errx(1, "fork error");
    }
    else if (pid == 0)
    {
        execvp(n->argv[0], n->argv);
    }
    int status;
    int r = waitpid(pid, &status, 0);
    if (r == -1)
        errx(1, "waitpid");

    char *temp = calloc(12, sizeof(char));
    temp = my_itoa(decode_status(status, s, n->argv[0]), temp);
    dvar_add_var(s->var, mstrdup("?"), temp);
}