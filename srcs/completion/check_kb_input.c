/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_kb_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:10:37 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 15:10:53 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"
#include <libft.h>
#include <sys/ioctl.h>
#include "sig_handler.h"
#define TAB_ACT_NB 8

static int		check_one(t_dat dat, t_editor *ed, char *line, char *buf)
{
	int i;

	i = 0;
	while (dat.buf[i] == buf[i] && i < 6)
		++i;
	if (i == 6)
	{
		dat.action(ed, line);
		return (1);
	}
	return (0);
}

void			check_tab_input(t_editor *ed, char *line)
{
	static t_dat	dat[] = {{{27, 91, 66, 0, 0, 0}, tab_down},
		{{9, 0, 0, 0, 0, 0}, tab_down}, {{'\n', 0, 0, 0, 0, 0}, tab_close},
		{{27, 91, 68, 0, 0, 0}, tab_left}, {{27, 91, 67, 0, 0, 0}, tab_right},
		{{27, 91, 65, 0, 0, 0}, tab_up}, {{3, 0, 0, 0, 0, 0}, tab_cancel},
		{{27, 0, 0, 0, 0, 0}, tab_cancel}};
	char			buf[7];
	int				i;

	ft_bzero(buf, 7);
	while (get_tabinfo()->select_mode && read(0, buf, 6))
	{
		i = -1;
		while (++i < TAB_ACT_NB)
			if (check_one(dat[i], ed, line, buf))
				break ;
		if (i == TAB_ACT_NB)
		{
			ioctl(0, TIOCSTI, buf);
			clear_tabinfo();
			break ;
		}
		ft_bzero(buf, 7);
	}
}
