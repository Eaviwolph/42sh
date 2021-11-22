/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:54:12 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 15:54:13 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"
#include "libft.h"

/*
** get options, if one wrong opt, consider there is no opt
** else: pass options to not display them
*/

int		builtin_echo(int argc, char **argv)
{
	int		i;
	char	*opt;

	if ((opt = get_options_core(argc, argv)) == (char *)-1)
		return (STATUS_FAILURE);
	i = 1;
	if (check_only_allowed_option(opt, "nse") == false)
		ft_strdel(&opt);
	else
		while (i < argc && argv[i][0] == '-' && \
		(argv[i][1] == 's' || argv[i][1] == 'n' || argv[i][1] == 'e'))
			i++;
	display_echo(argc, argv, opt, i);
	free(opt);
	return (STATUS_SUCCESS);
}

/*
** for every arguments:
** '-e': backslash escapes interpretation
** handle '-n' options
** '-s' option: do not display space for last str
*/

void	display_echo(int argc, char **argv, char *opt, int i)
{
	while (i < argc)
	{
		if (ft_strchr(opt, 'e') != NULL)
		{
			if (escape_char(argv[i]) == true)
				break ;
		}
		else
			ft_putstr(argv[i]);
		if (ft_strchr(opt, 's') == NULL && i + 1 < argc)
			ft_putchar(' ');
		i++;
	}
	if (ft_strchr(opt, 'n') == NULL)
		ft_putchar('\n');
}

/*
** Parcour every char
** if start with '\':
** if '\c' stop displaying
** display one char '\x' for two chars "\x"
** increment index to not display escaped chars
*/

bool	escape_char(char *str)
{
	int	i;
	int	oct;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '\\' && str[i + 1])
		{
			if (str[i + 1] == 'c')
				return (true);
			if (escape(*(&str[i + 1])) == true)
				i += 1;
			else if (str[i + 1] == '0' && (oct = octal(&str[i + 1])) > 0)
				i += 1 + oct;
			else
				ft_putchar(str[i]);
		}
		else
			ft_putchar(str[i]);
	}
	return (false);
}

/*
** return status if found char
*/

bool	escape(int c)
{
	char const	*escaped;
	char const	*ptr;

	escaped = "\\abefnrtv";
	if ((ptr = ft_strchr(escaped, c)) == NULL)
		return (false);
	ft_putchar("\\\a\b\e\f\n\r\t\v"[ptr - escaped]);
	return (true);
}

/*
** Check good format for octal: '\0NNN':
** [0-8], [0-8][0-8], [0-1][0-8][0-8]
** prevent segfault
** if not good format for three char: return
** substitute str, convert to int, convert to base 8 and print
** return number of char to not display
*/

int		octal(char *c)
{
	int		n;
	char	*str;
	int		nbr;
	int		len;

	n = 0;
	len = ft_strlen(c);
	if (3 < len && is_octal(c[3]) == true)
		n += 1;
	if (2 < len && is_octal(c[2]) == true)
		n += 1;
	if (1 < len && ((n == 2 && (c[1] == '0' || c[1] == '1')) ||
		(n < 2 && is_octal(c[1]) == true)))
		n += 1;
	if (n == 0)
		return (0);
	str = ft_strsub(c, 1, n);
	nbr = ft_atoi(str);
	ft_strdel(&str);
	ft_putchar((char)convert_base(nbr, 10, 8));
	return (n);
}
