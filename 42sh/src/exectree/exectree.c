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
            execand(n->data.binnode, s);
        }
        else if (n->type == OR)
        {
            execor(n->data.binnode, s);
        }
        else if (n->type == BANG)
        {
            execbang(n->data.binnode, s);
        }
        else if (n->type == PIPE)
        {
            execpipe(n->data.binnode, s);
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
            execsep(n->data.binnode, s);
        }
    }
}
