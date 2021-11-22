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

#ifndef ABSTRACT_LIST_H
# define ABSTRACT_LIST_H
# include <stdlib.h>
# include <stdbool.h>
# include "uint.h"

typedef struct				s_abstract_list
{
	struct s_abstract_list	*next;
}							t_abstract_list;

size_t						list_count(t_abstract_list const *list);

void						list_goto_last(t_abstract_list **list);
void						**list_pop_at_pos(size_t pos
							, t_abstract_list **list_addr);
void						list_push_at_pos(size_t pos,
								t_abstract_list **list_addr,
								t_abstract_list *elem);
void						list_push_back(t_abstract_list **list_addr
											, t_abstract_list *elem);
t_abstract_list const		*list_get_last_const(t_abstract_list const *list);
t_abstract_list				*list_dup_until(t_abstract_list const *list
						, t_abstract_list const *stop, size_t elem_size);
bool						list_goto_n(t_abstract_list **list, t_uint n);
void						list_concat(t_abstract_list	**dst
													, t_abstract_list *src);
void						list_free(t_abstract_list **list);

#endif
