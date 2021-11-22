/*
** exec_cmd.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sat Apr  8 07:38:48 2006 Seblu
** Last update Thu Nov 23 11:28:39 2006 seblu
*/

#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include "exec.h"
#include "../builtin/builtin.h"
#include "../common/function.h"

/*
** ============
** DECLARATIONS
** ============
*/

static int		exec_program(s_cmd_node *cmd);
static void		exec_function(char **argv);
static void		exec_argv(char **argv);
static void		exec_prefix(char **prefix, int glob);

/*!
** Debug execution
**
** @param cmd command
*/
static void		cmd_debugger(s_cmd_node *cmd);

/*
** ===========
** DEFINITIONS
** ===========
*/

void			exec_cmd(s_cmd_node *cmd)
{
  assert(cmd);
  if (DEBUG_EXEC)
    cmd_debugger(cmd);
  //FIXME: expansions here
  if (!cmd->argv) {
    if (cmd->prefix) exec_prefix(cmd->prefix, 0);
    return;
  }
  if (func_exist(shell->func, cmd->argv[0]))
    exec_function(cmd->argv);
  else if (is_a_builtin(cmd->argv[0]))
    shell->status = get_builtin(cmd->argv[0])(cmd->argv);
  else
    shell->status = exec_program(cmd);
}

void			exec_piped_cmd(s_cmd_node *cmd)
{
  assert(cmd);
  if (DEBUG_EXEC)
    cmd_debugger(cmd);
  //FIXME: expansions here
  if (!cmd->argv) {
    if (cmd->prefix) exec_prefix(cmd->prefix, 0);
    return;
  }
  if (func_exist(shell->func, cmd->argv[0]))
    exec_function(cmd->argv);
  else if (is_a_builtin(cmd->argv[0]))
    shell->status = get_builtin(cmd->argv[0])(cmd->argv);
  else {
    if (cmd->prefix)
      exec_prefix(cmd->prefix, 1);
    exec_argv(cmd->argv);
  }
}

static int		exec_program(s_cmd_node *cmd)
{
  pid_t			pid;
  int			status;

  if ((pid = fork()) == -1) {
    fprintf(stderr, "%s: Cannot fork.\n", shell->name);
    return ERROR_FORK;
  }
  if (pid) {
    waitpid(pid, &status, 0);
    return WEXITSTATUS(status);
  }
  if (cmd->prefix)
    exec_prefix(cmd->prefix, 1);
  exec_argv(cmd->argv);
  //never reach
  assert(0);
  return 1;
}

static void		exec_argv(char **argv)
{
  assert(argv && argv[0]);
  execvp(argv[0], argv);
  if (errno == ENOENT)
    if (strchr(argv[0], '/') == NULL)
      fprintf(stderr, "%s: %s: command not found.\n", shell->name, argv[0]);
    else
      fprintf(stderr, "%s: %s: No such file or directory.\n",
	      shell->name, argv[0]);
  else
    perror(shell->name);
  exit((errno == ENOENT) ? 127 : 126);
}

static void		exec_prefix(char **prefix, int glob)
{
  char			*value;

  assert(prefix);
  for (int i = 0; prefix[i]; ++i) {
    if (!(value = strchr(prefix[i], '=')))
      assert(0);
    *value = 0;
    if (glob || getenv(prefix[i]) != NULL)
      setenv2(prefix[i], value + 1, !0);
    else
      var_add(shell->var, prefix[i], value + 1);
    *value = '=';
  }
}

static void		exec_function(char **argv)
{
  assert(argv && argv[0]);
  //FIXME: add arguments transmission here
  exec_node(func_get(shell->func, argv[0]));
}


static void		cmd_debugger(s_cmd_node *cmd)
{
  int			i;

  fprintf(stderr, "-----------------------------------\n");
  fprintf(stderr, "exec command\n");
  for (i = 0; cmd->argv && cmd->argv[i]; ++i)
    fprintf(stderr, "argv[%d]   : %-15s\n", i, cmd->argv[i]);
  for (i = 0; cmd->prefix && cmd->prefix[i]; ++i)
    fprintf(stderr, "prefix[%d] : %-15s\n", i, cmd->prefix[i]);
  fprintf(stderr, "-----------------------------------\n");
}
