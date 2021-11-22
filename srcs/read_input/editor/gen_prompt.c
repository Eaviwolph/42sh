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
#include <unistd.h>

#include "utils.h"
#include "abstract_list.h"
#include "shell_env.h"

#include "read_input/editor/editor.h"
#include "read_input/editor/editor_struct.h"
#include "read_input/event_callbacks/event_callback_def.h"
#include "read_input/termcap/init_deinit.h"

#include "variable.h"
#include <sys/utsname.h>

static char const	*get_unmatched_str(t_error_id id)
{
	static t_unmatched_def	const	defs[] = {
		{ UNMATCHED_SINGLE_QUOTE, "quote" },
		{ UNMATCHED_DOUBLE_QUOTE, "dquote" },
		{ UNMATCHED_BACKQUOTE, "bquote" },
		{ UNEXPECTED_IF, "cmdif" },
		{ UNEXPECTED_PIPE, "pipe" },
	};
	size_t							u;

	u = 0;
	while (u < 6)
	{
		if (defs[u].id == id)
			return (defs[u].str);
		u++;
	}
	return ("unknown");
}

static char			*get_hostname(void)
{
	struct utsname	machine;

	if (uname(&machine) < 0)
		return (ft_strdup(""));
	return (ft_strdup(machine.nodename));
}

static char			*mangle_home(char *str)
{
	char	*result;
	char	*home_str;
	size_t	home_str_len;

	home_str = get_variable("HOME");
	if (home_str == NULL)
		return (str);
	result = ft_strstr(str, home_str);
	home_str_len = ft_strlen(home_str);
	free(home_str);
	if (result == NULL)
		return (str);
	result = ft_strjoin("~", result + home_str_len);
	free(str);
	return (result);
}

char				*gen_prompt(void)
{
	char		*result;
	char		*tmp;
	t_shell_env	*shell_env;

	shell_env = get_shell_env();
	if (!shell_env->last_unmatched)
	{
		tmp = ft_strjoinf(mangle_home(getcwd(0, 0)), "]$ ", 1);
		result = ft_strjoin(" ", tmp);
		free(tmp);
		tmp = ft_strjoinf(get_variable("USER"), "@", 1);
		tmp = ft_strjoinf(tmp, get_hostname(), 3);
		tmp = ft_strjoinf("[", tmp, 2);
		result = ft_strjoinf(tmp, result, 3);
	}
	else
		result = ft_strjoin(get_unmatched_str(shell_env->last_unmatched), "> ");
	return (result);
}
