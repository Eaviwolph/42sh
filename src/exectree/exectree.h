#ifndef EXECTREE_H
#define EXECTREE_H

#include "../shell/shell.h"
#include "../tree/tree.h"

int decode_status(int status);

void exectree(struct node *n, struct shell *s);
void execcmd(struct node_cmd n, struct shell *s);
void execand(struct node_bin n, struct shell *s);
void execor(struct node_bin n, struct shell *s);
void execbang(struct node_bin n, struct shell *s);
void execif(struct node_if n, struct shell *s);
void execfor(struct node_for n, struct shell *s);
void execwhile(struct node_while n, struct shell *s);
void execpipe(struct node_bin node, struct shell *s);
void execsep(struct node_bin n, struct shell *s);
void exefuncdec(struct node_funcdec n, struct shell *s);
int execfunc(struct node_cmd n, struct shell *s);
void execsubshell(struct node_bin n, struct shell *s);
void execred(struct node_red n, struct shell *s);
void execcase(struct node_case n, struct shell *s);

#endif
