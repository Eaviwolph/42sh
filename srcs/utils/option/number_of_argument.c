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

size_t	number_of_argument(char **argv)
{
	size_t	i;
	size_t	n;

	n = 0;
	i = 0;
	while (argv && argv[++i])
	{
		if (is_an_argument(argv, i))
		{
			n++;
		}
	}
	return (n);
}
