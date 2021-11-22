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
#include "utils.h"

char	*control_char_notation(char c)
{
	char *s;

	s = ft_strnew(2);
	s[0] = '^';
	if (c >= 0 && c <= 31)
		s[1] = c + 64;
	else if (c == 127)
		s[1] = '?';
	else
	{
		free(s);
		return (NULL);
	}
	return (s);
}

void	print_control_char_notation(char c)
{
	char *s;

	s = control_char_notation(c);
	ft_putstr(s);
	free(s);
}
