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

#ifndef STRLIST_H
# define STRLIST_H

# include <stdbool.h>

typedef struct			s_strlist
{
	struct s_strlist	*next;
	char				*str;
}						t_strlist;

t_strlist				*strlist_construct(char const *str);
char					**strlist_to_strarray(t_strlist const *list);
void					strlist_delete(t_strlist **strlist_addr);
void					strlist_append(t_strlist **strlist_addr,
							char const *str);
char					*strlist_to_str_until(t_strlist const *list,
							t_strlist const *end);
char					*strlist_to_str(t_strlist const *list);

#endif
