/*
** shell.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Mon Apr 10 23:57:28 2006 Seblu
** Last update Wed Nov 15 14:14:05 2006 seblu
*/

#include "shell.h"

#include <stdio.h>

#include "../ast/ast.h"
#include "../common/function.h"
#include "../common/macro.h"
#include "../exec/exec.h"
#include "../parser/parser.h"
#include "option.h"

/*
** ============
** DECLARATIONS
** ============
*/

/*
** Global shell structure
*/
s_shell *shell = NULL;

/*!
** Program entry point
**
** @param argc Argument count
** @param argv Argument vector
**
** @return return program value
*/
int main(int argc, char *argv[]);

/*!
** Initialize a shell structure
**
** @param path path of the current shell
**
** @return an initialized shell structure
*/
s_shell *shell_init(void);

/*
** ===========
** DEFINITIONS
** ===========
*/

int main(int argc, char *argv[])
{
    s_ast_node *ast;
    s_parser *parser;

    // shell initialization
    shell = shell_init();
    // Set shell name
    shell->name = basename(argv[0]);
    // Set default option
    option_set_default(shell->option);
    // parse argv for user options
    getoptions(shell->option, argc, argv);
    // FIXME: set shell env variables (eg. PWD, OLDPWD)
    // shell parser init
    parser = parser_init(STDIN_FILENO);
    // parse and execute stdin stream
    do
    {
        ast = parse(parser);
        if (parser->error && isinteractive())
            continue;
        else if (parser->error)
            return ERROR_PARSE;
        if (option_is_set(shell->option, "ast_print"))
            ast_print(ast, NULL);
        if (ast)
            exec_node(ast);
        ast_destruct(ast);
    } while (!parser->lexer->eof);
    if (isinteractive())
        fprintf(stderr, "exit\n");
    return shell->status;
}

s_shell *shell_init(void)
{
    s_shell *new;

    secmalloc(new, sizeof(s_shell));
    new->var = var_init();
    new->func = func_init();
    new->alias = alias_init();
    new->option = option_init();
    new->name = "42sh";
    new->status = 0;
    return new;
}
