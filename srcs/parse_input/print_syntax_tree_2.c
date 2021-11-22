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

#include "syntax_tree.h"
#include "print_syntax_tree.h"
#include "utils.h"
#include <libft.h>

static void	print_ao_sep(t_ao_type sep_type, size_t lvl)
{
	if (sep_type == AO_END)
		return ;
	print_n_char(' ', lvl * 2);
	if (sep_type == AO_AND)
		ft_putstr("&&");
	else if (sep_type == AO_OR)
		ft_putstr("||");
	else
		ft_putstr("BUG");
	ft_putchar('\n');
}

static void	print_and_or_list(t_and_or_list const *ao_list, size_t lvl)
{
	if (ao_list == NULL)
	{
		print_n_char(' ', lvl * 2);
		ft_putendl("empty");
		return ;
	}
	if (ao_list->next == NULL)
	{
		print_pipeline(ao_list->pipeline, lvl);
		return ;
	}
	print_n_char(' ', lvl * 2);
	ft_putendl("and_or_list:");
	while (ao_list != NULL)
	{
		print_pipeline(ao_list->pipeline, lvl + 1);
		if (ao_list->next != NULL)
			print_ao_sep(ao_list->separation_type, lvl);
		ao_list = ao_list->next;
	}
}

void		print_command_list(t_command_list const *cmd_list, size_t lvl)
{
	if (cmd_list == NULL)
	{
		print_n_char(' ', lvl * 2);
		ft_putendl("empty");
		return ;
	}
	if (cmd_list->next == NULL)
	{
		print_and_or_list(cmd_list->and_or_list, lvl);
		return ;
	}
	print_n_char(' ', lvl * 2);
	ft_putendl("command_list:");
	while (cmd_list != NULL)
	{
		print_and_or_list(cmd_list->and_or_list, lvl + 1);
		cmd_list = cmd_list->next;
		if (cmd_list != NULL)
		{
			print_n_char(' ', lvl * 2);
			ft_putchar(';');
			ft_putchar('\n');
		}
	}
}
