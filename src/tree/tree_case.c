#include "../tools/tools.h"
#include "tree.h"

struct node *tree_case_create(char *word)
{
    struct node *node;

    safe_calloc(node, 1, sizeof(struct node));
    node->type = CASE;
    node->data.casenode.word = mystrdup(word);
    return node;
}

void tree_case_add_item(struct node *node, char **pattern, struct node *exec)
{
    size_t len = 0;
    while (pattern[len])
    {
        len++;
    }
    char **pat = calloc(len + 1, sizeof(char *));
    for (size_t i = 0; i < len; i++)
    {
        pat[i] = mystrdup(pattern[i]);
    }
    free(pattern);
    struct node_case_item *item;
    safe_calloc(item, 1, sizeof(struct node_case_item));
    item->pattern = pat;
    item->exec = exec;
    struct node_case_item *this;
    if (!node->data.casenode.items)
    {
        node->data.casenode.items = item;
    }
    else
    {
        this = node->data.casenode.items;
        while (this->next)
        {
            this = this->next;
        }
        this->next = item;
    }
}

void tree_case_print(struct node *node, FILE *fs)
{
    fprintf(fs, "case (%s)\n", node->data.casenode.word);
    struct node_case_item *item = node->data.casenode.items;
    while (item)
    {
        for (int i = 0; item->pattern[i]; i++)
            fprintf(fs, "%s: ", item->pattern[i]);
        tree_print_node(item->exec, fs);
        fprintf(fs, "\n");
        item = item->next;
    }
}

static void rec_case_destroy(struct node_case_item *this)
{
    if (this)
    {
        rec_case_destroy(this->next);
        for (int i = 0; this->pattern[i]; i++)
            free(this->pattern[i]);
        free(this->pattern);
        tree_destroy(this->exec);
        free(this);
    }
}

void tree_case_destroy(struct node *node)
{
    free(node->data.casenode.word);
    rec_case_destroy(node->data.casenode.items);
    free(node);
}
