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

#include <stdbool.h>
#include <libft.h>
#include "utils.h"

bool	is_an_argument(char **argv, int pos)
{
	if (ft_tablen(argv) <= pos)
		return (false);
	if (!ft_strcmp(ARG_STOP, argv[pos]))
		return (false);
	return (!is_an_option(argv, pos));
}
