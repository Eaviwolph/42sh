#include "../tools/tools.h"
#include "tree.h"

struct node *tree_red_create(void)
{
    struct node *node;

    safe_calloc(node, 1, sizeof(struct node));
    node->type = RED;
    return node;
}

void tree_red_add(struct node *node, enum red_type type, int fd, char *word)
{
    node->data.rednode.size += 1;

    safe_realloc(node->data.rednode.type, node->data.rednode.type,
                 sizeof(enum red_type) * node->data.rednode.size);
    node->data.rednode.type[node->data.rednode.size - 1] = type;

    safe_realloc(node->data.rednode.fd, node->data.rednode.fd,
                 sizeof(int) * node->data.rednode.size);
    node->data.rednode.fd[node->data.rednode.size - 1] = fd;

    safe_realloc(node->data.rednode.word, node->data.rednode.word,
                 sizeof(char *) * node->data.rednode.size);
    node->data.rednode.word[node->data.rednode.size - 1] = mystrdup(word);
}

void tree_red_print(struct node *node, FILE *fs)
{
    fprintf(fs, "red ");
    for (size_t i = 0; i < node->data.rednode.size; ++i)
        fprintf(fs, "fd=%d, type=%d, word=%s ", node->data.rednode.fd[i],
                node->data.rednode.type[i], node->data.rednode.word[i]);
    if (node->data.rednode.mhs)
        tree_print_node(node->data.rednode.mhs, fs);
}

void tree_red_destroy(struct node *node)
{
    free(node->data.rednode.type);
    free(node->data.rednode.fd);
    for (size_t i = 0; i < node->data.rednode.size; i++)
    {
        free(node->data.rednode.word[i]);
    }
    free(node->data.rednode.word);
    tree_destroy(node->data.rednode.mhs);
    free(node);
}
