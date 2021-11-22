/*
** exec_subshell.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sat Apr 15 08:54:51 2006 Seblu
** Last update Fri Nov 17 14:23:49 2006 seblu
*/

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>
#include "exec.h"
#include "../common/constant.h"

void		exec_subshell(s_bin_node *node)
{
   pid_t	pid;
   int		status;

   assert(node && node->lhs);
   if ((pid = fork()) == -1) {
     fprintf(stderr, "%s: %s.\n", shell->name, strerror(errno));
     shell->status = ERROR_FORK;
     return;
   }
   if (pid) {
     waitpid(pid, &status, 0);
     shell->status = WEXITSTATUS(status);
   }
   else {
     exec_node(node->lhs);
     exit(ERROR_FORK);
   }
}
