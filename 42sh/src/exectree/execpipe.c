#define _POSIX_SOURCE

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../tools/tools.h"
#include "exectree.h"

struct pipeline
{
    int p[2];
    int pid[2];
};

static pid_t exec_side(struct node *right, struct pipeline *pipeline, int side,
                       struct shell *s)
{
    int nside = 0;
    if (side == 0)
        nside = 1;
    int pid = fork();
    if (pid == -1)
        return -1;
    if (pid == 0)
    {
        dup2(pipeline->p[side], side);
        close(pipeline->p[nside]);
        exectree(right, s);
        exit(atoi(dvar_find(s->var, "?")));
        return pid;
    }
    close(pipeline->p[side]);
    pipeline->pid[side] = pid;
    return pid;
}

void execpipe(struct node_bin node, struct shell *s)
{
    struct pipeline *pipeline = calloc(1, sizeof(struct pipeline));
    if (pipe(pipeline->p) || exec_side(node.right, pipeline, 0, s) < 0
        || exec_side(node.left, pipeline, 1, s) < 0)
    {
        fprintf(stderr, "%s: %s.\n", s->name, strerror(errno));
        dvar_add_var(s->var, mystrdup("?"), mystrdup("128"));
    }
    else
    {
        int status;
        waitpid(pipeline->pid[0], &status, 0);
        char *st = calloc(12, sizeof(char));
        st = myitoa(WEXITSTATUS(status), st);
        dvar_add_var(s->var, mystrdup("?"), st);
    }
    int status;
    kill(pipeline->pid[1], SIGPIPE);
    waitpid(pipeline->pid[1], &status, 0);
    free(pipeline);
}
