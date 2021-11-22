/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_on_tty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 16:28:06 by asenat            #+#    #+#             */
/*   Updated: 2017/06/22 17:18:48 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_env.h"
#include <libft.h>
#include "put_on_tty.h"

void	putchar_on_tty(const char c)
{
	ft_putchar_fd(c, get_shell_env()->tty_fd);
}

void	putstr_on_tty(const char *str)
{
	ft_putstr_fd(str, get_shell_env()->tty_fd);
}

void	putendl_on_tty(const char *str)
{
	ft_putendl_fd(str, get_shell_env()->tty_fd);
}
