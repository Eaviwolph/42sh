/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/14 18:18:59 by pilespin          #+#    #+#             */
/*   Updated: 2015/10/09 17:02:19 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		i;

	va_start(ap, format);
	i = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == 's')
				ft_putstr_fd(va_arg(ap, char*), fd);
			if (format[i] == 'd')
				ft_putnbr_fd(va_arg(ap, int), fd);
			i++;
		}
		while ((format[i] != '%') && (format[i]))
		{
			ft_putchar_fd(format[i], fd);
			i++;
		}
	}
	return (0);
}
