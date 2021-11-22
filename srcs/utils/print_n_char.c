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

void	print_n_char_fd(char c, size_t n, int fd)
{
	while (n > 0)
	{
		n--;
		ft_putchar_fd(c, fd);
	}
}

void	print_n_char(char c, size_t n)
{
	print_n_char_fd(c, n, STDOUT_FILENO);
}
