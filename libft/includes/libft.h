/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 12:28:51 by pilespin          #+#    #+#             */
/*   Updated: 2017/06/29 12:50:12 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LIBFT_H
# define FT_LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <sys/time.h>
# include "get_next_line.h"

# define BUFF_SIZE 4095

void		ft_putchar(char c);
void		ft_putcharc(int color, int background, char str);
void		ft_putnchar(int x, char c);
void		ft_putchar_fd(char c, int fd);
void		ft_putstr(char const *s);
void		ft_putstrc(int color, int background, char *str, int fd);
void		ft_putstr_fd(char const *s, int fd);
void		ft_putendl(char const *s);
void		ft_putendl_fd(char const *s, int fd);
int			ft_printf(const char*format, ...);
int			ft_dprintf(int fd, const char*format, ...);
void		ft_putnbr(int n);
void		ft_putnbr_fd(int n, int fd);
void		ft_puttab(char **tab);
void		ft_puttab3(char ***tab);
void		ft_puttabint(int **tab);

void		ft_sorttab(char **tab);
void		ft_swap_char(char **tab, int i, int j);
void		*ft_memalloc(size_t size);
void		*memalloc_or_die(size_t size);
void		ft_memdel(void **ap);
void		ft_strdel(char **as);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memset(void *b, int c, size_t len);
void		ft_strclr(char *s);
char		*ft_strcpy(char *dst, const char *src);
char		*ft_strncpy(char *dst, const char *src, size_t n);
size_t		ft_strlcat(char *dst, const char *src, size_t size);

size_t		ft_strlen(const char *s);
size_t		ft_strlen_char(const char *s, char car);
int			ft_tablen(char **tab);
int			ft_intlen(int x);

char		*ft_strnew(size_t size);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
char		*ft_strcat(char *s1, const char *s2);
char		*ft_strncat(char *s1, const char *s2, size_t n);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strstr(const char *s1, const char *s2);
char		*ft_strnstr(const char *s1, const char *s2, size_t n);
int			ft_strequ(char const *s1, char const *s2);
int			ft_strnequ(char const *s1, char const *s2, size_t n);

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_ispair(int num);
int			ft_isimpair(int num);
int			is_octal(char c);

int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

char		*ft_itoa(int c);
char		*ft_itoabig(long long c);
char		*ft_itoaf(double nbr);
int			ft_atoi(const char *str);
long long	ft_atoibig(const char *str);
double		ft_atof(const char *str);

char		*ft_strdup(const char *s1);
char		*ft_strdup_add_space(char *s);
char		*ft_strdup_whitout_space(char *s);
char		*ft_strrev(const char *s1);
char		*ft_strndup(const char *s1, int len);
char		*ft_strdupf(char *s1);
char		**ft_tabdup(char **s1);

char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin_max(int nbr_arg, char *str, ...);
char		*ft_strjoinf(char const *s1, char const *s2, int i);
char		**ft_strsplit(char const *s, char c);
char		*ft_implode(char **tab);
char		**ft_strsplit_start(char const *s, char c, int start);
char		*ft_strtrim(char const *s);
void		ft_striter(char *s, void(*f)(char *));
void		ft_striteri(char *s, void(*f)(unsigned int, char *));
char		*ft_strmap(char const *s, char(*f)(char));
char		*ft_strmapi(char const *s, char(*f)(unsigned int, char));
int			ft_get_next_line(int const fd, char **line);

char		**ft_make_tabchar(int size);

void		ft_freetabchar(char **as);

double		ft_pow(double x, double y);
double		ft_sqrt(double nbr);
int			ft_absint(int x);

double		ft_utime(void);
int			ft_random(int min, int max);

void		ft_replace_char(char *line, char del, char add);
int			ft_count_char(char *str, char car);

char		**ft_splitfilepath(char *file);
void		ft_doublearrayndel(void ***a, size_t n);

#endif
