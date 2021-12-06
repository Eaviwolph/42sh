#include "tree.h"

void tree_destroy(struct node *node)
{
    if (node)
    {
        if (node->type == IF)
            tree_if_destroy(node);
        else if (node->type == FOR)
            tree_for_destroy(node);
        else if (node->type == WHILE)
            tree_while_destroy(node);
        else if (node->type == CMD)
            tree_cmd_destroy(node);
        else if (node->type == AND)
            tree_and_destroy(node);
        else if (node->type == OR)
            tree_or_destroy(node);
        else if (node->type == SUBSHELL)
            tree_subshell_destroy(node);
        else if (node->type == FUNCDEC)
            tree_funcdec_destroy(node);
        else if (node->type == BANG)
            tree_bang_destroy(node);
        else if (node->type == PIPE)
            tree_pipe_destroy(node);
        else if (node->type == SEPAND)
            tree_sepand_destroy(node);
        else if (node->type == SEP)
            tree_sep_destroy(node);
        else if (node->type == CASE)
            tree_case_destroy(node);
        else if (node->type == RED)
            tree_red_destroy(node);
    }
}