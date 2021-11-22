/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 13:30:37 by asenat            #+#    #+#             */
/*   Updated: 2017/06/29 12:49:50 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_content	*init_content(int fd, char *content)
{
	t_content *res;

	if (!(res = (t_content*)malloc(sizeof(struct s_content))))
		return (NULL);
	res->fd = fd;
	res->rest = content;
	return (res);
}

t_list		*getlist(int fd, t_list **lst)
{
	t_list		*tmp;
	t_content	*new;

	new = init_content(fd, NULL);
	tmp = *lst;
	if (!*lst)
	{
		*lst = ft_lstnew(new, sizeof(struct s_content));
		ft_memdel((void**)(&new));
		return (*lst);
	}
	while (tmp)
	{
		if (((t_content*)(tmp->content))->fd == fd)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		ft_lstadd(lst, ft_lstnew(new, sizeof(struct s_content)));
		ft_memdel((void**)(&new));
		return (*lst);
	}
	ft_memdel((void**)(&new));
	return (tmp);
}

int			readline(int fd, t_list *lst, char **line)
{
	int			loc;
	char		*red;
	t_content	*ctnt;

	ctnt = (t_content*)(lst->content);
	red = ft_realloc(ft_strdup(ctnt->rest), BUFF_SIZE);
	while (!ft_strchr(red, '\n'))
	{
		if (read(fd, (red + ft_strlen(red)), BUFF_SIZE) <= 0)
			break ;
		red = ft_realloc(red, BUFF_SIZE);
	}
	loc = (ft_strchr(red, '\n')) ? ft_strchr(red, '\n') - red : -1;
	if (loc < 0)
	{
		*line = ft_strdup(red);
		ft_memdel((void**)(&red));
		ft_strdel(&(ctnt->rest));
		return ((**line == '\0') ? 0 : 1);
	}
	ft_strdel(&(ctnt->rest));
	ctnt->rest = ft_strsub(red, loc + 1, ft_strlen(red) - loc);
	*line = ft_strsub(red, 0, loc);
	ft_memdel((void**)(&red));
	return (1);
}

int			get_next_line(int const fd, char **line)
{
	static t_list	*lst = NULL;
	t_list			*current;

	if (fd < 0 || !line)
		return (-1);
	if (read(fd, 0, 0) == -1)
		return (-1);
	current = getlist(fd, &lst);
	return (readline(fd, current, line));
}
