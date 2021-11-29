#include "parser.h"

#include <assert.h>
#include <errno.h>
#include <setjmp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../common/function.h"
#include "../common/macro.h"
#include "dtoken.h"
#include "../tree/tree.h"

struct node *parse(struct dtoken *tokens)
{
    if (!tokens)
        return NULL;
    struct node *n;
    safe_malloc(n, sizeof(struct node));
    n->type = IF;
    struct node_if k = { NULL, NULL, NULL };
    n->data.ifnode = k;
    return n;
}