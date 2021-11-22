/*
** exec_pipe.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Wed Apr 12 01:52:31 2006 Seblu
** Last update Fri Nov 17 13:51:22 2006 seblu
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include "exec.h"
#include "../common/constant.h"

/*
** ============
** DECLARATIONS
** ============
*/

typedef struct		pipeline
{
  int			count;
  int			last;
  pid_t			*list;
} s_pipeline;

/*!
** Initialize a pipeline structure
**
** @param pipeline pipele struct to init
*/
static void		init_pipeline(s_pipeline *pipeline);

/*!
** Push an pid to the pipeline
**
** @param pipeline list of pid
** @param new new pid to add
*/
static void		push_pid(s_pipeline *ls, pid_t new);

/*!
** Pop the first pid pushed (FILE)
**
** @param pipeline pipeline
**
** @return the first pid pushed
*/
static pid_t		pop_pid(s_pipeline *ls);

/*!
** Execute a pipe sequence
**
** @param pipeline pipeline info
** @param node pipe node to execute
**
** @return 0 if pipe fail, else 1
*/
static int		exec_pipeline(s_pipeline *pipeline, s_bin_node *node);

/*!
** Wait process exit status
**
** @param pipeline the pipeline of process id
** @param killer if true, destroy all open process
*/
static void		wait_controler(s_pipeline *pipeline, int killer);

/*!
** Execute a command writer on the pipe
**
** @param p the pipe
** @param left command to execute
** @param pipeline pipeline information
** @param sh shell structure
**
** @return pid for father, exit with last_status for the son
*/
static pid_t		exec_left_hand(int			p[2],
				       s_ast_node		*left,
				       s_pipeline		*pipeline);
/*!
** Execute a command reader on the pipe
**
** @param p the pipe
** @param right command to execute
** @param pipeline pipeline information
** @param sh shell structure
**
** @return pid for father, exit with last_status for the son
*/
static pid_t		exec_right_hand(int			p[2],
					s_ast_node		*right,
					s_pipeline		*pipeline);

/*
** ===========
** DEFINITIONS
** ===========
*/

void			exec_pipe(s_bin_node *node)
{
  int			ret;
  s_pipeline		pipeline;

  assert(node);
  init_pipeline(&pipeline);
  if (!(ret = exec_pipeline(&pipeline, node))) {
    fprintf(stderr, "%s: %s.\n", shell->name, strerror(errno));
    shell->status = ERROR_PIPE;
  }
  wait_controler(&pipeline, !ret);
  free(pipeline.list);
}

static int		exec_pipeline(s_pipeline *pipeline, s_bin_node *node)
{
  int			p[2];
  pid_t			pid;
  int			save;
  int			ret;

  if (pipe(p))
    return 0;
  if ((pid = exec_right_hand(p, node->rhs, pipeline)) < 0)
    return 0;
  if (node->lhs->type == T_PIPE) {
    save = dup(STDOUT_FILENO);
    dup2(p[1], STDOUT_FILENO);
    close(p[1]);
    ret = exec_pipeline(pipeline, &node->lhs->body.child_pipe);
    dup2(save, STDOUT_FILENO);
    close(save);
    return ret;
  }
  return (exec_left_hand(p, node->lhs, pipeline) < 0) ? 0 : 1;
}

static void		wait_controler(s_pipeline *pipeline, int killer)
{
  int			status;
  pid_t			pid;

  if (!killer) {
    pid = pop_pid(pipeline);
    waitpid(pid, &status, 0);
    status = WEXITSTATUS(status);
    shell->status = WEXITSTATUS(status);
  }
  while ((pid = pop_pid(pipeline)) != -1)
  {
    kill(pid, SIGPIPE);
    waitpid(pid, &status, 0);
    status = WEXITSTATUS(status);
  }
}

static pid_t		exec_right_hand(int		p[2],
					s_ast_node	*right,
					s_pipeline	*pipeline)
{
  int			pid;

  if ((pid = fork()) == -1)
    return -1;
  if (pid)
  {
    close(p[0]);
    push_pid(pipeline, pid);
    return pid;
  }
  dup2(p[0], STDIN_FILENO);
  close(p[1]);
  if (right->type == T_CMD)
    exec_piped_cmd(&right->body.child_cmd);
  else
    exec_node(right);
  exit(shell->status);
  return pid;
}

static pid_t		exec_left_hand(int		p[2],
				       s_ast_node	*left,
				       s_pipeline	*pipeline)
{
  int			pid;

  if ((pid = fork()) == -1)
    return -1;
  if (pid) {
    close(p[1]);
    push_pid(pipeline, pid);
    return pid;
  }
  dup2(p[1], STDOUT_FILENO);
  close(p[0]);
  if (left->type == T_CMD)
    exec_piped_cmd(&left->body.child_cmd);
  else
    exec_node(left);
  exit(shell->status);
  return pid;
}

static void		init_pipeline(s_pipeline *pipeline)
{
  assert(pipeline);
  pipeline->count = 0;
  pipeline->last = -1;
  pipeline->list = NULL;
}

static void		push_pid(s_pipeline *pipeline, pid_t new)
{
  assert(pipeline);
  if (new < 0)
    return;
  secrealloc(pipeline->list, pipeline->list, ++pipeline->count * sizeof (pid_t));
  pipeline->list[pipeline->count - 1] = new;
}

static pid_t		pop_pid(s_pipeline *pipeline)
{
  assert(pipeline);
  if (pipeline->count <= 0 || pipeline->last + 1 >= pipeline->count)
    return -1;
  return pipeline->list[++pipeline->last];
}
