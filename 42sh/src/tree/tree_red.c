#include "tree.h"

struct node *tree_red_create(void)
{
    struct node *node;

    secmalloc(node, sizeof(struct node));
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
    secrealloc(reds->type, reds->type, sizeof(enum red_type) * reds->size);
    reds->type[reds->size - 1] = type;
    secrealloc(reds->fd, reds->fd, sizeof(int) * reds->size);
    reds->fd[reds->size - 1] = fd;
    secrealloc(reds->word, reds->word, sizeof(char *) * reds->size);
    reds->word[reds->size - 1] = word;
}

void tree_red_print(struct node *node, FILE *fs, unsigned *node_id)
{
    unsigned cur_id = *node_id;

    if (node->type != RED)
        return;
    struct node_red *reds = (struct node_red *)&node->data.rednode;
    if (reds->size == 0)
        return;
    fprintf(fs, "%u [label = \"Redirection\\n", *node_id);
    ++*node_id;
    for (register size_t i = 0; i < reds->size; ++i)
        fprintf(fs, "id=%zu, fd=%d, type=%d, word=%s\\n", i, reds->fd[i],
                reds->type[i], reds->word[i]);
    fprintf(fs, "\"];\n");
    fprintf(fs, "%u -> %u\n", cur_id, *node_id);
    if (reds->mhs)
        ast_print_node(reds->mhs, fs, node_id);
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
    ast_destruct(node->data.rednode.mhs);
    ast_red_destruct_node(node);
}
