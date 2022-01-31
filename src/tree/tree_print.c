#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "tree.h"

void tree_print_node(struct node *node, FILE *stream)
{
    if (node)
    {
        if (node->type == IF)
            tree_if_print(node, stream);
        else if (node->type == FOR)
            tree_for_print(node, stream);
        else if (node->type == WHILE)
            tree_while_print(node, stream);
        else if (node->type == CMD)
            tree_cmd_print(node, stream);
        else if (node->type == AND)
            tree_and_print(node, stream);
        else if (node->type == OR)
            tree_or_print(node, stream);
        else if (node->type == SUBSHELL)
            tree_subshell_print(node, stream);
        else if (node->type == FUNCDEC)
            tree_funcdec_print(node, stream);
        else if (node->type == BANG)
            tree_bang_print(node, stream);
        else if (node->type == PIPE)
            tree_pipe_print(node, stream);
        else if (node->type == SEPAND)
            tree_sepand_print(node, stream);
        else if (node->type == SEP)
            tree_sep_print(node, stream);
        else if (node->type == CASE)
            tree_case_print(node, stream);
        else if (node->type == RED)
            tree_red_print(node, stream);
    }
}
