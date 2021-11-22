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

bool	is_special_builtin(char *builtin)
{
	static char *special_builtins[] = {"exit", "unset", "export", NULL};
	size_t		i;

	i = 0;
	while (special_builtins[i])
	{
		if (!ft_strcmp(special_builtins[i], builtin))
			return (true);
		i++;
	}
	return (false);
}
