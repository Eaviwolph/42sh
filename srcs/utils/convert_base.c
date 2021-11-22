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

/*
** generic function to handle conversion of base
** Should works till 999
*/

int		convert_base(int nbr, int base_from, int base_to)
{
	int	ret;

	ret = 0;
	if (nbr >= base_from * base_from)
	{
		ret += base_to * base_to;
		nbr -= base_from * base_from;
	}
	while (nbr >= base_to)
	{
		ret += base_to;
		nbr -= base_from;
	}
	return (ret + nbr);
}
