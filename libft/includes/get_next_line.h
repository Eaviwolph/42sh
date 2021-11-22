/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 13:30:59 by asenat            #+#    #+#             */
/*   Updated: 2017/06/29 13:03:00 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

# include "libft.h"
# include <fcntl.h>

typedef struct	s_content
{
	int		fd;
	char	*rest;
}				t_content;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

int				get_next_line(int const fd, char **line);
t_list			*ft_lstnew(void const *content, size_t content_size);
void			*ft_realloc(void *target, size_t size);
void			ft_lstadd(t_list **ast, t_list *new);

#endif
