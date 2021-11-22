/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:18:31 by asenat            #+#    #+#             */
/*   Updated: 2017/06/27 17:32:57 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"
#include "variable.h"
#include "put_on_tty.h"
#include <libft.h>
#include <term.h>
#include <sys/stat.h>

t_tabinfo	*get_tabinfo(void)
{
	static t_tabinfo inf;

	return (&inf);
}

void		clear_tabinfo(void)
{
	t_strlist *l;

	l = get_tabinfo()->list;
	strlist_delete(&l);
	free(get_tabinfo()->file_prefix);
	free(get_tabinfo()->total_word);
	ft_bzero(get_tabinfo(), sizeof(t_tabinfo));
}

void		add_file(t_strlist **lst, struct dirent *dir, char *prepath)
{
	char			*tmp;
	char			*for_stat;
	char			*escaped;
	struct stat		my_stat;

	if (!ft_strcmp(dir->d_name, ".") || !ft_strcmp(dir->d_name, ".."))
		return ;
	tmp = ft_strdup(dir->d_name);
	for_stat = ft_strjoinf(prepath, dir->d_name, 0);
	stat(for_stat, &my_stat);
	if (S_ISDIR(my_stat.st_mode))
		tmp = ft_strjoinf(tmp, "/", 1);
	escaped = str_escape(tmp, " \\;|<>'\"");
	list_push_back((t_abstract_list**)&lst,
			(t_abstract_list*)strlist_construct(escaped));
	ft_strdel(&tmp);
	ft_strdel(&for_stat);
	ft_strdel(&escaped);
}

void		clear_down(t_editor *ed)
{
	int save;

	save = ed->cursor_position;
	tputs(tgetstr("sc", 0), 1, ft_rputchar);
	while (ed->cursor_position < ed->string_size)
		ev_cursor_right(ed);
	tputs(tgetstr("cd", 0), 1, ft_rputchar);
	ed->cursor_position = save;
	tputs(tgetstr("rc", 0), 1, ft_rputchar);
}

char		*replace_home(char *s)
{
	char	*ret;
	int		i;
	char	*tmp;
	char	*home;

	home = get_variable("HOME");
	if (!s || !home || home[0] == '\0' || s[0] != '~')
	{
		ft_strdel(&home);
		return (s);
	}
	ret = ft_strnew(ft_strlen(home) + ft_strlen(s) - 1);
	i = ft_strlen(home);
	ft_strcpy(ret, home);
	tmp = s;
	s++;
	while (*s)
		ret[i++] = *s++;
	ft_strdel(&tmp);
	ft_strdel(&home);
	return (ret);
}
