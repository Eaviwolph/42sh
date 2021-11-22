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

#include "libft.h"
#include "tabenv.h"

/*
** Browse env var
*/

char	*get_tenv(char **env, char *var)
{
	int	i;

	i = -1;
	if (env != NULL)
		while (env[++i] != NULL)
			if (ft_strcmp(env[i], var) == 61)
				return (ft_strchr(env[i], '=') + 1);
	return (NULL);
}
