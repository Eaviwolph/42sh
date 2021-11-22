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

#ifndef EDITOR_STRUCT_H
# define EDITOR_STRUCT_H

# include "shell_env.h"
# include <stdbool.h>
# include "vec2i.h"

typedef struct			s_unmatched_def
{
	t_error_id			id;
	char const			*str;
}						t_unmatched_def;

typedef struct			s_string
{
	struct s_string		*next;
	char				c;
}						t_string;

typedef struct			s_term
{
	bool				rescue_mode;
	int					width;
	int					rows;
	char				*move_cursor_begining;
	char				*move_left;
	char				*move_right;
	char				*move_up;
	char				*move_down;
	char				*hide_cursor;
	char				*show_cursor;
	char				*clear_line;
}						t_term;

typedef struct			s_editor
{
	bool				in_selection;
	bool				selected;
	size_t				selected_string_start;
	size_t				selected_string_end;
	char				*selected_string;
	char				*history_saved_current_string;
	t_string			*string;
	t_term				*term;
	t_history			*history;
	t_history			*history_current;
	size_t				old_position;
	t_vec2i				pos;
	size_t				cursor_position;
	size_t				string_size;
	size_t				prompt_size;
	char				*prompt;
	bool				need_refresh;
	bool				action_move_left;
	bool				in_edition;
	bool				in_history;
	int					last_event;
}						t_editor;

#endif
