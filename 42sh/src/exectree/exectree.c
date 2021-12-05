#include "exectree.h"

void exectree(struct node *n, struct shell *s)
{
    if (n)
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
            execpipe(n->data.pipenode, s);
        }
        else if (n->type == IF)
        {
            execif(n->data.ifnode, s);
        }
        else if (n->type == FOR)
        {
            execfor(n->data.fornode, s);
        }
        else if (n->type == WHILE)
        {
            execwhile(n->data.whilenode, s);
        }
        else if (n->type == SEP)
        {
            execsep(n->data.sepnode, s);
        }
    }
}