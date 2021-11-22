/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42shTeam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 15:35:21 by 42shTeam          #+#    #+#             */
/*   Updated: 2017/05/03 15:35:21 by 42shTeam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "abstract_list.h"
#include "utils.h"
#include "file_positions.h"
#include <errno.h>

void			history_add_with_nl(t_shell_env *shell_env, char *line)
{
	char	*tmp;

	tmp = ft_strjoin(line, "\n");
	add_to_history_list(&shell_env->history.list, create_history_entry(tmp));
	ft_strdel(&tmp);
}

t_file_position	*get_file_position(char *filename)
{
	t_file_position *files;

	files = get_shell_env()->history_files;
	while (files)
	{
		if (!ft_strcmp(files->filename, filename))
			return (files);
		files = files->next;
	}
	return (NULL);
}

static void		new_file_position(char *filename, int position)
{
	t_file_position *new;

	new = memalloc_or_die(sizeof(t_file_position));
	new->filename = ft_strdup(filename);
	new->position = position;
	new->next = NULL;
	list_push_back((t_abstract_list **)&get_shell_env()->history_files, \
					(t_abstract_list *)new);
}

void			update_file_position(char *filename, int new_position)
{
	t_file_position *files;

	if (!(files = get_file_position(filename)))
		new_file_position(filename, new_position);
	else
		files->position = new_position;
}

void			load_history(t_shell_env *shell_env, char *filename,
							bool n_opt)
{
	char	*line;
	int		fd;
	int		i;
	int		position;

	i = 0;
	position = 0;
	line = NULL;
	if (!filename)
		filename = get_shell_env()->history.histfile;
	if ((fd = open(filename, O_RDONLY)) >= 0)
	{
		if (n_opt)
			position = get_file_position(filename)->position;
		while ((get_next_line(fd, &line)))
		{
			if (i >= position)
				history_add_with_nl(shell_env, line);
			ft_strdel(&line);
			i++;
		}
		ft_strdel(&line);
		close(fd);
		update_file_position(filename, i);
	}
}
