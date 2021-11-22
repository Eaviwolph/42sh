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

#ifndef EDITOR_H
# define EDITOR_H

# include "read_input/editor/editor_struct.h"
# include "vec2i.h"

void		init_editor();
t_editor	*get_editor();
void		add_to_string(t_editor *ed, char c);
char		*get_string_from_list(t_string *s);
void		free_string(t_string *s);
void		close_history(t_editor *ed);
char		*gen_prompt(void);
t_vec2i		get_cursor_vector(t_editor *ed);
void		move_cursor(t_vec2i	vec, t_term *term);
void		move_cursor_to(t_vec2i old_pos, t_vec2i new_pos, t_term *term);
t_vec2i		vec2i_sub(t_vec2i a, t_vec2i b);

void		clear_line(t_editor *ed);
void		put_line(t_editor *ed);
void		move_start(t_editor *ed);
void		refresh_line(t_editor *ed);
void		free_editor(t_editor *ed);

void		put_highlighted_line(t_editor *ed, char *line);
void		swap_position_if_needed(t_editor *ed);
void		clear_selected_pos(t_editor *ed);

size_t		find_index_at_vector(t_editor *ed, int ox, int oy);
t_vec2i		get_cursor_vector(t_editor *ed);
bool		if_on_multiline(t_editor *ed);
void		change_string(t_editor *ed, char *line);
void		str_to_list_in_editor(t_editor *ed, char *str);

#endif
