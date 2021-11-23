/*
** ast_print.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sat Mar 25 23:11:01 2006 Seblu
** Last update Thu Oct 19 13:02:30 2006 seblu
*/

#include <assert.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#include "ast.h"

typedef void (*f_print)(s_ast_node *, FILE *, unsigned int *);

struct ast_print_switch
{
    e_node_type type;
    f_print fct;
};

struct ast_print_switch print_table[NODE_TYPE_COUNT] = {
    { T_IF, ast_if_print },
    { T_FOR, ast_for_print },
    { T_WHILE, ast_while_print },
    { T_CMD, ast_cmd_print },
    { T_AND, ast_and_print },
    { T_OR, ast_or_print },
    { T_SUBSHELL, ast_subshell_print },
    { T_FUNCDEC, ast_funcdec_print },
    { T_BANG, ast_bang_print },
    { T_PIPE, ast_pipe_print },
    { T_SEPAND, ast_sepand_print },
    { T_SEP, ast_sep_print },
    { T_CASE, ast_case_print },
    { T_RED, ast_red_print }
};

static char *newastfilename(void);

void ast_print(s_ast_node *ast, const char *filename)
{
    FILE *fs;
    unsigned int index = 0;

    if (ast == NULL)
        return;
    // open file stream
    if (!filename)
        filename = newastfilename();
    if (!(fs = fopen(filename, "w")))
        return;
    // write dot header
    fprintf(fs, "digraph \"42sh-ast\" {\n");
    fprintf(fs, "node [fontname=Vera, color=lightblue2, style=filled];\n");
    // start ast node wrinting
    ast_print_node(ast, fs, &index);
    // write dot foot and close
    fprintf(fs, "}");
    fclose(fs);
}

void ast_print_node(s_ast_node *ast, FILE *fs, unsigned int *node_id)
{
    assert(ast);
    for (register int i = 0; i < NODE_TYPE_COUNT; ++i)
        if (print_table[i].type == ast->type)
            (print_table[i].fct)(ast, fs, node_id);
}

static char *newastfilename(void)
{
    static char buf[PATH_MAX];
    time_t st;
    struct tm *t;
    struct stat buf2;
    int more = 0;

    st = time(NULL);
    t = localtime(&st);
    do
        snprintf(buf, 256, "/tmp/42sh-ast-%d-%d-%d-%d-%d-%d--%d.dot",
                 1900 + t->tm_year, 1 + t->tm_mon, t->tm_mday, t->tm_hour,
                 t->tm_min, t->tm_sec, more++);
    while (stat(buf, &buf2) != -1 && more < 50);
    return buf;
}
