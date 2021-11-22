/*
** env.c for 42sh
**
** Made by seblu
** Login   <seblu@epita.fr>
**
** Started on  Tue Nov 14 14:38:42 2006 seblu
** Last update Tue Nov 14 15:37:46 2006 seblu
*/

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include "function.h"

int		setenv2(char	*name,
			char	*value,
			int	overwrite)
{
  extern char	**environ;
  char		*buf;
  char		**env = environ;
  size_t	len;

  assert(name && value && env);
  len = strlen(name);
  if (!overwrite)
    for (; *env; ++env)
      if (!strncmp(name, *env, len) && (*env)[len] == '=')
	return 1;
  buf = strmerge(3, name, "=", value);
  return !putenv(buf) ? 0 : 2;
}

int		unsetenv2(const char *name)
{
  extern char	**environ;
  size_t	len;
  char		**ep = environ;
  char		**dp = ep;

  if (name == NULL || *name == '\0' || strchr(name, '=') != NULL)
  {
    errno = EINVAL;
    return -1;
  }
  len = strlen(name);
  for (; *ep; ++ep)
  {
    if (!strncmp(*ep, name, len) && (*ep)[len] == '=')
    {
      dp = ep;
      do
	dp[0] = dp[1];
      while (++dp, *dp);
    }
  }
  return 0;
}
