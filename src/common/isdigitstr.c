/*
** isdigitstr.c for 42sh
**
** Made by Seblu
** Login   <seblu@seblu.net>
**
** Started on  Sun Nov 13 08:13:54 2005 Seblu
** Last update Tue Aug 22 22:43:54 2006 Seblu
*/

int		isdigitstr(const char *str)
{
  if (*str == 0)
    return 0;
  for (; *str; str++)
    if (!(*str >= '0' && *str <= '9'))
      return 0;
  return 1;
}
