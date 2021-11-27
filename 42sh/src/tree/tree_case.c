#include "tree.h"

struct node *tree_case_create(char *word)
{
    struct node *node;

    secmalloc(node, sizeof(struct node));
    node->type = CASE;
    node->data.casenode.word = word;
    node->data.casenode.items = NULL;
    return node;
}

void tree_case_add_item(struct node *node, char **pattern, struct node *exec)
{
    struct node_case_item *item;
    struct node_case_item **this;

    if (node->type != CASE)
        return;
    secmalloc(item, sizeof(struct node_case_item));
    item->pattern = pattern;
    item->exec = exec;
    item->next = NULL;
    for (this = &node->data.casenode.items; *this; this = &(*this)->next)
        ; // do nothing
    *this = item;
}

void tree_case_print(struct node *node, FILE *fs, unsigned *node_id)
{
    unsigned cur_node;
    struct node_case_item *item;
    unsigned item_id;
    unsigned item_node;

    if (node->type != CASE)
        return;
    fprintf(fs, "%u [label = \"CASE\\nword: %s\"];\n", cur_node = *node_id,
            node->data.casenode.word);
    ++*node_id;
    // show items
    for (item = node->data.casenode.items, item_id = 0; item;
         item = item->next, ++item_id)
    {
        fprintf(fs, "%u -> %u\n", cur_node, *node_id);
        fprintf(fs, "%u [label = \"Item %u\\n", item_node = *node_id, item_id);
        ++*node_id;
        // print pattern
        if (item->pattern)
            for (int i = 0; item->pattern[i]; ++i)
                fprintf(fs, "%s\\n", item->pattern[i]);
        fprintf(fs, "\"];\n");
        // print exec
        if (item->exec)
        {
            fprintf(fs, "%u -> %u\n", item_node, *node_id);
            ast_print_node(item->exec, fs, node_id);
        }
    }
}

void tree_case_destroy_node(struct node *node)
{
    struct node_case_item *this;
    struct node_case_item *buf;

    if (node->type != CASE)
        return;
    free(node->data.casenode.word);
    for (this = node->data.casenode.items; this; this = buf)
    {
        for (register int i = 0; this->pattern[i]; ++i)
            free(this->pattern[i]);
        free(this->pattern);
        buf = this->next;
        free(this);
    }
    free(node);
}

void tree_case_destroy(struct node *node)
{
    struct node_case_item *this;
    struct node_case_item *buf;

    if (node->type != CASE)
        return;
    free(node->data.casenode.word);
    for (this = node->data.casenode.items; this; this = buf)
    {
        for (register int i = 0; this->pattern[i]; ++i)
            free(this->pattern[i]);
        free(this->pattern);
        ast_destruct(this->exec);
        buf = this->next;
        free(this);
    }
    free(node);
}
