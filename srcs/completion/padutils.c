/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:10:58 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 15:11:53 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"
#include "put_on_tty.h"
#include <term.h>

int		getpad(t_strlist *l, int line)
{
	int		i;
	int		pad;
	char	*cur;

	i = 0;
	pad = 0;
	while (l && i < line)
	{
		cur = (char*)l->str;
		if ((size_t)pad < ft_strlen(cur))
			pad = ft_strlen(cur);
		l = l->next;
		i++;
	}
	return (pad);
}

void	print_pad(int pad, char *str)
{
	int spaces;

	spaces = pad - ft_strlen(str);
	putstr_on_tty(str);
	while (spaces--)
	{
		if (spaces == 2)
			tputs(tgetstr("me", 0), 1, ft_rputchar);
		putchar_on_tty(' ');
	}
}
