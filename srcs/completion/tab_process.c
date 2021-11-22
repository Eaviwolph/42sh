/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:16:16 by asenat            #+#    #+#             */
/*   Updated: 2017/06/27 17:21:01 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "read_input/event_callbacks/event_callback_def.h"
#include "completion.h"
#include <paths.h>

char				*get_cur_word(int curspos, char *line)
{
	int		i;
	char	*ret;

	i = 0;
	while (curspos && line[curspos - 1] != ' ')
	{
		--curspos;
		++i;
	}
	ret = ft_strsub(line, curspos, i);
	return (replace_home(ret));
}

static t_strlist	*get_files(char *path)
{
	char			**split;
	DIR				*dir;
	struct dirent	*dirent;
	t_strlist		*l;

	split = ft_splitfilepath(path);
	if (!(dir = (split[0]) ? opendir(split[0]) : opendir(".")))
	{
		ft_freetabchar(split);
		return (NULL);
	}
	l = NULL;
	while ((dirent = readdir(dir)))
		if (!ft_strncmp(dirent->d_name, split[1], ft_strlen(split[1])))
			add_file(&l, dirent, split[0]);
	(get_tabinfo()->file_prefix) ? free(get_tabinfo()->file_prefix) : 0;
	get_tabinfo()->file_prefix = str_escape(split[1], " \\;|<>'\"");
	ft_doublearrayndel((void***)&split, 2);
	closedir(dir);
	asciisort(&l);
	return (l);
}

static t_strlist	*get_binaries(char *bin)
{
	char		*tmp;
	char		**spath;
	int			i;
	t_strlist	*ret;

	if (!(tmp = get_variable("PATH")))
		tmp = ft_strdup(_PATH_DEFPATH);
	spath = ft_strsplit(tmp, ':');
	ft_strdel(&tmp);
	i = -1;
	ret = NULL;
	while (spath[++i])
	{
		if (spath[i][ft_strlen(spath[i]) - 1] != '/')
			spath[i] = ft_strjoinf(spath[i], "/", 1);
		spath[i] = ft_strjoinf(spath[i], bin, 1);
		list_push_back((t_abstract_list**)&ret,
				(t_abstract_list*)get_files(spath[i]));
	}
	ft_freetabchar(spath);
	return (ret);
}

void				choice_tab(t_editor *ed, char *line,
						char *path, int first_word)
{
	t_strlist	*l;

	if (ed->last_event == TAB_EVID)
	{
		get_tabinfo()->select_mode = 1;
		tab_display(ed, line, get_tabinfo());
		check_tab_input(ed, line);
		ft_strdel(&path);
		ed->last_event = -1;
		return ;
	}
	clear_tabinfo();
	l = (first_word) ? get_binaries(path) : get_files(path);
	if (l)
	{
		get_tabinfo()->list = l;
		get_tabinfo()->total_word = path;
		tab_display(ed, line, get_tabinfo());
	}
	else
		ft_strdel(&path);
}
