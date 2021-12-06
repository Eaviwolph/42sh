#include "exectree.h"

void execsep(struct node_bin n, struct shell *s)
{
    exectree(n.left, s);
    if (n.right)
        exectree(n.right, s);
}
