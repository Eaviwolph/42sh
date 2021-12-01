#ifndef EXECTREE_H
#define EXECTREE_H

#include "../shell/shell.h"
#include "../tree/tree.h"

void exectree(struct node *n, struct shell *s);
void execcmd(struct node_cmd *n, struct shell *s);
void execand(struct node_and *n, struct shell *s);
void execor(struct node_or *n, struct shell *s);

#endif