/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errno_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:35:08 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 15:35:25 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <errno.h>
#include "errors.h"

void		print_errno_error(int err, char const *pre, char const *post)
{
	ft_putstr_fd("42sh: ", 2);
	if (pre != NULL)
	{
		ft_putstr_fd(pre, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(get_system_error(err), 2);
	if (post != NULL)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(post, 2);
	}
	ft_putchar_fd('\n', 2);
}
