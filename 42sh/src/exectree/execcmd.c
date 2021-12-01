#define _GNU_SOURCE
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../tools/tools.h"
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

void execcmd(struct node_cmd n, struct shell *s)
{
    int pid = fork();
    if (pid == -1)
    {
        errx(1, "fork error");
    }
    else if (pid == 0)
    {
        execvp(n.argv[0], n.argv);
        exit(EXIT_FAILURE);
    }
    int status;
    int r = waitpid(pid, &status, 0);
    if (r == -1)
        errx(1, "waitpid");

    char *temp = calloc(12, sizeof(char));
    temp = myitoa(decode_status(status, s, n.argv[0]), temp);
    dvar_add_var(s->var, mystrdup("?"), temp);
}