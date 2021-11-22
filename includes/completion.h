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

#ifndef COMPLETION_H
# define COMPLETION_H

# include <dirent.h>
# include "abstract_list.h"
# include "strlist.h"
# include "read_input/event_callbacks/event_callbacks.h"

# undef tab

typedef struct		s_tabinfo
{
	int			select_mode;
	int			selected_index;
	int			nb_lines;
	char		*file_prefix;
	char		*total_word;
	t_strlist	*list;
}					t_tabinfo;

typedef struct		s_dat
{
	char	buf[7];
	void	(*action)(t_editor*, char*);
}					t_dat;

char				*get_cur_word(int curspos, char *line);
void				tab_display(t_editor *ed, char *line, t_tabinfo *info);
void				check_tab_input(t_editor *ed, char *line);
void				add_file(t_strlist **lst, struct dirent *dir,
						char *prepath);
t_tabinfo			*get_tabinfo(void);
void				clear_tabinfo(void);
void				clear_down(t_editor *ed);
void				asciisort(t_strlist **lst);
char				*replace_home(char *s);
char				*str_escape(char *s, char *to_escape);
void				choice_tab(t_editor *ed, char *line, char *path,
						int first_word);
int					getpad(t_strlist *l, int line);
void				print_pad(int pad, char *str);

void				tab_down(t_editor *ed, char *line);
void				tab_up(t_editor *ed, char *line);
void				tab_left(t_editor *ed, char *line);
void				tab_right(t_editor *ed, char *line);
void				tab_close(t_editor *ed, char *line);
void				tab_cancel(t_editor *ed, char *line);

#endif
