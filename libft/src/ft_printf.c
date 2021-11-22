/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pilespin <pilespin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 17:54:42 by pilespin          #+#    #+#             */
/*   Updated: 2015/03/08 17:02:13 by pilespin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *format, ...)
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
				ft_putstr(va_arg(ap, char*));
			if (format[i] == 'd')
				ft_putnbr(va_arg(ap, int));
			i++;
		}
		while ((format[i] != '%') && (format[i]))
		{
			ft_putchar(format[i]);
			i++;
		}
	}
	va_end(ap);
	return (0);
}
