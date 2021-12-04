#ifndef EXECTREE_H
#define EXECTREE_H

#include "../shell/shell.h"
#include "../tree/tree.h"

void exectree(struct node *n, struct shell *s);
void execcmd(struct node_cmd n, struct shell *s);
void execand(struct node_and n, struct shell *s);
void execor(struct node_or n, struct shell *s);
void execbang(struct node_bang n, struct shell *s);
void execif(struct node_if n, struct shell *s);
void execfor(struct node_for n, struct shell *s);
void execwhile(struct node_while n, struct shell *s);
void execpipe(struct node_pipe node, struct shell *s);

#endif