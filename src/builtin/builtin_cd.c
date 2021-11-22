/*
** builtin_cd.c for 42sh
**
** Made by Seblu
** Login   <seblu@epita.fr>
**
** Started on  Tue Apr 11 00:23:47 2006 Seblu
** Last update Thu Nov 16 16:57:54 2006 seblu
*/

#include <stdio.h>
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../common/function.h"
#include "../shell/shell.h"
#include "../shell/var.h"

/*
** ============
** DECLARATIONS
** ============
*/

/*!
** Change directory to home directory
**
** @param name env var
**
** @return success status
*/
static int	cd_var(const char *name);

/*!
** Change of directory and on error, print good error.
**
** @param path new path
**
** @return error status with error code (0 is good)
*/
static int	secure_chdir(const char *path);

/*
** ===========
** DEFINITIONS
** ===========
*/

int		builtin_cd(char **argv)
{
  assert(argv && argv[0]);

  if (!argv[1])
    return cd_var("HOME");
  if (!strcmp("-", argv[1]))
    return cd_var("OLDPWD");
  return secure_chdir(argv[1]);
}

static int	cd_var(const char *name)
{
  const char	*new_dir;

  if (!(new_dir = var_get(shell->var, name))) {
    fprintf(stderr, "%s: cd: %s not set\n", shell->name, name);
    return 1;
  }
  return secure_chdir(new_dir);
}

static int	secure_chdir(const char *path)
{
  char		*tmp;

  if (chdir(path)) {
    fprintf(stderr, "%s: cd %s: %s\n", shell->name, path, strerror(errno));
    return 1;
  }
  //FIXME: getenv return name=val and setenv2 take cut arguments
  if ((tmp = getenv("PWD")))
    setenv2("OLDPWD", tmp, !0);
  setenv2("PWD", (tmp = getcwd2()), !0);
  return 0;
}
