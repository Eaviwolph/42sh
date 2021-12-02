#include "exectree.h"

void exectree(struct node *n, struct shell *s)
{
    if (n->type == CMD)
    {
        execcmd(n->data.cmdnode, s);
    }
    else if (n->type == AND)
    {
        execand(n->data.andnode, s);
    }
    else if (n->type == OR)
    {
        execor(n->data.ornode, s);
    }
    else if (n->type == BANG)
    {
        execbang(n->data.bangnode, s);
    }
    else if (n->type == PIPE)
    {
        exec_pipe(n->data.pipenode, s);
    }
}