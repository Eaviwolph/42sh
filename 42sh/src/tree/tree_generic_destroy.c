#include "tree.h"

struct tree_destruct_dictionary_elem
{
    enum node_type type;
    void (*fct)(struct node *);
};

struct tree_destruct_dictionary_elem dic[NODE_TYPE_COUNT] = {
    { IF, tree_if_destroy },
    { FOR, tree_for_destroy },
    { WHILE, tree_while_destroy }/*,
    { CMD, tree_cmd_destroy },
    { AND,treet_and_destroy },
    { OR, tree_or_destroy },
    { SUBSHELL, tree_subshell_destroy },
    { FUNCDEC, tree_funcdec_destroy },
    { BANG, tree_bang_destroy },
    { PIPE, tree_pipe_destroy },
    { SEPAND, tree_sepand_destroy },
    { SEP, tree_sep_destroy },
    { CASE, tree_case_destroy },
    { RED, tree_red_destroy }*/
};

struct tree_destruct_dictionary_elem dic_node[NODE_TYPE_COUNT] = {
    { IF, tree_if_destroy_node },
    { FOR, tree_for_destroy_node },
    { WHILE, tree_while_destroy_node }/*,
    { CMD, tree_cmd_destroy_node },
    { AND, tree_and_destroy_node },
    { OR, tree_or_destroy_node },
    { SUBSHELL, tree_subshell_destroy_node },
    { FUNCDEC, tree_funcdec_destroy_node },
    { BANG, tree_bang_destroy_node },
    { PIPE, tree_pipe_destroy_node },
    { SEPAND, tree_sepand_destroy_node },
    { SEP, tree_sep_destroy_node },
    { CASE, tree_case_destroy_node },
    { RED, tree_red_destroy_node }*/
};

void tree_destroy(struct node *tree)
{
    if (tree == NULL)
        return;
    for (register int i = 0; i < NODE_TYPE_COUNT; ++i)
        if (dic[i].type == tree->type)
        {
            (dic[i].fct)(tree);
            return;
        }
}

void tree_destroy_node(struct node *tree)
{
    if (tree == NULL)
        return;
    for (register int i = 0; i < NODE_TYPE_COUNT; ++i)
        if (dic_node[i].type == tree->type)
        {
            (dic_node[i].fct)(tree);
            return;
        }
}
