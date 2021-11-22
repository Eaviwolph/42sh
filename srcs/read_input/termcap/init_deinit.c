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

#include <libft.h>
#include <term.h>
#include <termios.h>
#include <curses.h>
#include "utils.h"
#include "shell_env.h"
#include "abstract_list.h"
#include "read_input/editor/editor.h"
#include "read_input/event_callbacks/event_callback_def.h"

static void				set_rescue_mode(t_term *new)
{
	new->rescue_mode = true;
}

t_term					*init_term(void)
{
	t_term *new;

	new = memalloc_or_die(sizeof(t_term));
	if ((new->width = tgetnum("co")) == -1 ||
		(new->rows = tgetnum("li")) == -1)
		set_rescue_mode(new);
	if ((new->move_cursor_begining = tgetstr("cr", NULL)) == NULL)
		set_rescue_mode(new);
	if ((new->move_left = tgetstr("le", NULL)) == NULL)
		set_rescue_mode(new);
	if ((new->move_right = tgetstr("nd", NULL)) == NULL)
		set_rescue_mode(new);
	if ((new->move_up = tgetstr("up", NULL)) == NULL)
		set_rescue_mode(new);
	if ((new->move_down = tgetstr("down", NULL)) == NULL)
		set_rescue_mode(new);
	if ((new->hide_cursor = tgetstr("vi", NULL)) == NULL)
		set_rescue_mode(new);
	if ((new->show_cursor = tgetstr("ve", NULL)) == NULL)
		set_rescue_mode(new);
	if ((new->clear_line = tgetstr("cd", NULL)) == NULL)
		set_rescue_mode(new);
	return (new);
}

static struct termios	*get_term_save(void)
{
	static struct termios term;

	return (&term);
}

void					ft_start_termcaps(void)
{
	struct termios	term;
	char			*env;

	env = get_variable("TERM");
	if (!env || tgetent(NULL, env) == ERR ||
		tcgetattr(0, &term) == -1)
	{
		free(env);
		ft_dprintf(2, "%s: I need a variable \"TERM\"\n", SHNAME);
		exit(-1);
	}
	ft_memcpy(get_term_save(), &term, sizeof(struct termios));
	term.c_lflag &= ~(ICANON | ECHO | ISIG);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
	{
		free(env);
		ft_dprintf(2, "%s: Termcap is lost\n", SHNAME);
		exit(-1);
	}
	free(env);
}

void					ft_close_termcaps(void)
{
	if (tcsetattr(0, 0, get_term_save()) == -1)
	{
		ft_dprintf(2, "%s: Termcap is lost\n", SHNAME);
		exit(-1);
	}
}
