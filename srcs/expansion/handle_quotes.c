/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 17:08:54 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 17:08:58 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

void		handle_quotes(char c, char *quoted)
{
	if (c == '\'')
	{
		if (*quoted & IS_QU_SIMPLE)
			*quoted -= IS_QU_SIMPLE;
		else
			*quoted |= IS_QU_SIMPLE;
	}
	else if (c == '\"')
	{
		if (*quoted & IS_QU_DOUBLE)
			*quoted -= IS_QU_DOUBLE;
		else
			*quoted |= IS_QU_DOUBLE;
	}
}
