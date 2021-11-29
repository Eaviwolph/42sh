#include "tree.h"

struct node *tree_case_create(char *word)
{
    struct node *node;

    safe_malloc(node, sizeof(struct node));
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
    safe_malloc(item, sizeof(struct node_case_item));
    item->pattern = pattern;
    item->exec = exec;
    item->next = NULL;
    this = &node->data.casenode.items;
    for (; *this; this = &(*this)->next)
        ; // do nothing
    *this = item;
}

void tree_case_print(struct node *node, FILE *fs)
{
    struct node_case_item *item;

    if (node->type != CASE)
        return;
    fprintf(fs, "case ");
    // show items
    int item_id;
    for (item = node->data.casenode.items, item_id = 0; item;
         item = item->next, ++item_id)
    {
        fprintf(fs, "%u ", item_id);
        // print pattern
        if (item->pattern)
            for (int i = 0; item->pattern[i]; ++i)
                fprintf(fs, "%s: ", item->pattern[i]);
        // print exec
        if (item->exec)
        {
            tree_print_node(item->exec, fs);
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
        tree_destroy(this->exec);
        buf = this->next;
        free(this);
    }
    free(node);
}
