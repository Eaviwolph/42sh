/*
** exec_pipe.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Apr 12 01:52:31 2006 Seblu
** Last update Fri Nov 17 13:51:22 2006 seblu
*/
#define _POSIX_SOURCE
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "../common/macro.h"
#include "../tools/tools.h"
#include "exectree.h"

typedef struct pipeline
{
    int count;
    int last;
    pid_t *list;
    int p[2];
} s_pipeline;

static pid_t pop_pid(s_pipeline *pipeline)
{
    if (pipeline->count <= 0 || pipeline->last + 1 >= pipeline->count)
        return -1;
    return pipeline->list[++pipeline->last];
}

static void push_pid(s_pipeline *pipeline, pid_t new)
{
    if (new < 0)
        return;
    safe_realloc(pipeline->list, pipeline->list,
                 ++pipeline->count * sizeof(pid_t));
    pipeline->list[pipeline->count - 1] = new;
}

static void wait_controler(s_pipeline *pipeline, int killer, struct shell *s)
{
    int status;
    pid_t pid;
    if (!killer)
    {
        pid = pop_pid(pipeline);
        waitpid(pid, &status, 0);
        status = WEXITSTATUS(status);
        char *str = calloc(12, sizeof(char));
        str = myitoa(WEXITSTATUS(status), str);
        dvar_add_var(s->var, mystrdup("?"), str);
    }
    while ((pid = pop_pid(pipeline)) != -1)
    {
        kill(pid, SIGPIPE);
        waitpid(pid, &status, 0);
    }
}

static pid_t exec_hand(struct node *n, s_pipeline *pipeline, struct shell *s,
                       int side)
{
    int pid = fork();

    if (pid == -1)
        return -1;
    if (pid == 0)
    {
        dup2(pipeline->p[side], side);
        close(pipeline->p[!side]);
        exectree(n, s);
        exit(atoi(dvar_find(s->var, "?")));
        return 0;
    }
    close(pipeline->p[side]);
    push_pid(pipeline, pid);
    return pid;
}

static int exec_pipeline(s_pipeline *pipeline, struct node_pipe node,
                         struct shell *s)
{
    int ret = 0;

    pipe(pipeline->p);
    pid_t pid = exec_hand(node.right, pipeline, s, 0);
    if (pid >= 0)
    {
        /*if (node.left->type == PIPE)
        {
            int save = dup(STDOUT_FILENO);
            dup2(pipeline->p[1], STDOUT_FILENO);
            close(pipeline->p[1]);
            ret = exec_pipeline(pipeline, node.left->data.pipenode, s);
            dup2(save, STDOUT_FILENO);
            close(save);
        }
        else */if (exec_hand(node.left, pipeline, s, 1) >= 0)
        {
            ret = 1;
        }
    }
    return ret;
}

void exec_pipe(struct node_pipe node, struct shell *s)
{
    int ret;
    s_pipeline *pipeline = calloc(1, sizeof(s_pipeline));
    pipeline->last = -1;
    if (!(ret = exec_pipeline(pipeline, node, s)))
    {
        fprintf(stderr, "%s: %s.\n", s->name, strerror(errno));
        char *str = calloc(12, sizeof(char));
        str = myitoa(128, str);
        dvar_add_var(s->var, mystrdup("?"), str); // error pipe
    }
    wait_controler(pipeline, !ret, s);
    free(pipeline->list);
    free(pipeline);
}
