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

#ifndef HISTORY_DEBUG_H
# define HISTORY_DEBUG_H

# include <libft.h>
# include "shell_env.h"
# include "history_options.h"
# include "range.h"

void			print_history_options(t_hist_opt *options);
void			print_range(t_range *range);
void			print_subst(t_str_subst subst);

#endif
