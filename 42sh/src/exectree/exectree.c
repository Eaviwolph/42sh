#include "exectree.h"
void exectree(struct node *n, struct shell *s)
{

    if (n->type == CMD)
    {
        execcmd(&n->data.cmdnode, s);
    }
    else if (n->type == AND)
    {
        execand(&n->data.andnode, s);
    }
}