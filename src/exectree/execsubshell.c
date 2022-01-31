#include <err.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../tools/tools.h"
#include "exectree.h"

void execsubshell(struct node_bin n, struct shell *s)
{
    // forking
    int pid = fork();
    if (pid == -1)
    {
        errx(1, "fork error");
    }
    else if (pid == 0)
    {
        if (n.left)
            exectree(n.left, s);
        if (n.right)
            exectree(n.right, s);
        if (errno == ENOENT)
            fprintf(stderr, "%s: subshell error.\n", s->name);
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