#include "tree.h"

struct node *tree_red_create(void)
{
    struct node *node;

    safe_malloc(node, sizeof(struct node));
    node->type = RED;
    node->data.rednode.size = 0;
    node->data.rednode.type = NULL;
    node->data.rednode.fd = NULL;
    node->data.rednode.word = NULL;
    node->data.rednode.mhs = NULL;
    return node;
}

void tree_red_add(struct node *node, enum red_type type, int fd, char *word)
{
    if (node->type != RED)
        return;
    struct node_red *reds = (struct node_red *)&node->data.rednode;
    ++reds->size;
    safe_realloc(reds->type, reds->type, sizeof(enum red_type) * reds->size);
    reds->type[reds->size - 1] = type;
    safe_realloc(reds->fd, reds->fd, sizeof(int) * reds->size);
    reds->fd[reds->size - 1] = fd;
    safe_realloc(reds->word, reds->word, sizeof(char *) * reds->size);
    reds->word[reds->size - 1] = word;
}

void tree_red_print(struct node *node, FILE *fs)
{
    if (node->type != RED)
        return;
    struct node_red *reds = (struct node_red *)&node->data.rednode;
    if (reds->size == 0)
        return;
    fprintf(fs, "red ");
    for (register size_t i = 0; i < reds->size; ++i)
        fprintf(fs, "id=%zu, fd=%d, type=%d, word=%s ", i, reds->fd[i],
                reds->type[i], reds->word[i]);
    if (reds->mhs)
        tree_print_node(reds->mhs, fs);
}

void tree_red_destroy_node(struct node *node)
{
    struct node_red *reds;

    if (node->type != RED)
        return;
    reds = (struct node_red *)&node->data.rednode;
    if (reds->size)
    {
        free(reds->type);
        free(reds->fd);
        for (register size_t i = 0; i < reds->size; ++i)
            free(reds->word[i]);
        free(reds->word);
    }
    free(node);
}

void tree_red_destroy(struct node *node)
{
    if (node->type != RED)
        return;
    tree_destroy(node->data.rednode.mhs);
    tree_and_destroy_node(node);
}
