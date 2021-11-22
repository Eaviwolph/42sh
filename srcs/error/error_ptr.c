/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:34:41 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 15:34:47 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

static t_error_id		*get_error_ptr(void)
{
	static t_error_id	error;

	return (&error);
}

t_error_id				get_error(void)
{
	return (*get_error_ptr());
}

void					set_error(t_error_id error)
{
	*(get_error_ptr()) = error;
}
