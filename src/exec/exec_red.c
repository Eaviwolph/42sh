/*
** exec_red.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Sun Nov 12 16:39:51 2006 Seblu
** Last update Fri Nov 17 13:16:51 2006 seblu
*/

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "exec.h"
#include "../common/constant.h"

/*
** ===========
** MACROS
** ===========
*/

#pragma GCC diagnostic ignored "-Wimplicit-fallthrough"

#define rederror(file, msg) do { fprintf(stderr, "%s: %s: %s.\n", \
 shell->name, file, msg); return ERROR_PIPE; } while (0)

#define is_open_read(flags) (((flags) & 0x3) == O_RDONLY || \
 ((flags) & 0x2) == O_RDWR)

#define is_open_write(flags) (((flags) & 0x3) == O_WRONLY || \
 ((flags) & 0x2) == O_RDWR)

/*
** ============
** DECLARATIONS
** ============
*/

typedef struct		red_context
{
  int			old; //old fd number
  int			save; //save of old fd
} s_red_context;

/*!
** Save the current red context
**
** @param reds red node
**
** @return a struct that contains all current redirection context
*/
static s_red_context	*save_red_context(s_red_node *reds);

/*!
** Restore a previous redirection context and free it
**
** @param context context to restore
*/
static void		restore_red_context(s_red_context *context);

/*!
** Apply redirections
**
** @param reds red node
**
** @return success status
*/
static int		apply_red(s_red_node *reds);

/*!
** Retrieve an fd from a word
**
** @param txt fd in string
**
** @return -1 if fail, -2 for close fd else fd
*/
static int		get_filedes(const char *txt);

/*
** ===========
** DEFINITIONS
** ===========
*/

void			exec_red(s_red_node *red)
{
  s_red_context		*context;

  assert(red);
  //FIXME: expansion on red here
  context = save_red_context(red);
  shell->status = apply_red(red);
  if (!shell->status)
    exec_node(red->mhs);
  restore_red_context(context);
}

static s_red_context	*save_red_context(s_red_node *reds)
{
  s_red_context		*context;
  register size_t		i;

  secmalloc(context, (reds->size + 1) * sizeof (s_red_context));
  for (i = 0; i < reds->size; ++i) {
    context[i].old = reds->fd[i];
    context[i].save = dup(reds->fd[i]);
  }
  context[i].old = -1;
  return context;
}

static void		restore_red_context(s_red_context *context)
{
  for (register int i = 0; context[i].old != - 1; ++i)
    dup2(context[i].save, context[i].old);
  free(context);
}

static int		apply_red(s_red_node *reds)
{
  int			fd;

  assert(reds);
  for (size_t i = 0; i < reds->size; ++i) {
    switch (reds->type[i]) {
    case R_LESS: // <
      if ((fd = open(reds->word[i], O_RDONLY)) == -1)
	rederror(reds->word[i], strerror(errno));
      dup2(fd, reds->fd[i]);
      close(fd);
      break;
    case R_GREAT: // >
      if (option_is_set(shell->option, "noclobber") &&
	  !access(reds->word[i], F_OK))
	rederror(reds->word[i], "cannot overwrite existing file");
    case R_CLOBBER: // >|
      if ((fd = open(reds->word[i], O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1)
	rederror(reds->word[i], strerror(errno));
      dup2(fd, reds->fd[i]);
      close(fd);
      break;
    case R_DGREAT: // >>
      if ((fd = open(reds->word[i], O_WRONLY | O_CREAT | O_APPEND, 0666)) == -1)
	rederror(reds->word[i], strerror(errno));
      dup2(fd, reds->fd[i]);
      close(fd);
      break;
    case R_GREATAND: // >&
    case R_LESSAND: // <&
      fd = get_filedes(reds->word[i]);
      int flags;
      if (fd == -1)
	rederror(reds->word[i], "ambiguous redirect");
      else if (fd == -2 && close(reds->fd[i]))
	rederror(reds->word[i], strerror(errno));
      else if ((flags = fcntl(fd, F_GETFL)) == -1)
	rederror(reds->word[i], strerror(errno));
      if (reds->type[i] == R_GREATAND && !is_open_write(flags))
	rederror(reds->word[i], "fd not open for writing");
      if (reds->type[i] == R_LESSAND && !is_open_read(flags))
	rederror(reds->word[i], "fd not open for reading");
      dup2(fd, reds->fd[i]);
      break;
    case R_LESSGREAT: // <>
      assert(0);
      //FIXME
      break;
    case R_DLESS: // <<
      assert(0);
      /*       if ((fd = mkstemp(filename = strdup("42sh.heredocs.XXXXXX"))) == -1) */
      /* 	rederror("42sh"); */
      /*       write(fd, reds[i]->file, strlen(reds[i]->file)); */
      /*       lseek(fd, 0, SEEK_SET); */
      /*       unlink(filename); */
      /*       free(filename); */
      /*       dup2(fd, STDIN_FILENO); */
      /*       close(fd); */
      break;
    case R_DLESSDASH: // <<-
      assert(0);
      //FIXME
      break;
    default:
      fprintf(stderr, "%s: Invalid redirection.\n", shell->name);
      assert(0);
      return ERROR_RED;
    }
  }
  return 0;
}

static int		get_filedes(const char *txt)
{
  long			fd;
  char			*endbuf;

  assert(txt);
  if (txt[0] == '-' && txt[1] == 0)
    return -2;
  fd = strtol(txt, &endbuf, 10);
  if (endbuf == txt || *endbuf != 0)
    return -1;
  return fd;
}
