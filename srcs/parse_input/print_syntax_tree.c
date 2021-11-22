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
#include "utils.h"
#include <libft.h>

static void		print_assignments(t_variable const *a, size_t lvl)
{
	if (a == NULL)
		return ;
	print_n_char(' ', (lvl) * 2);
	ft_putstr("assignment(s):");
	while (a != NULL)
	{
		ft_putchar(' ');
		ft_putstr(a->name);
		ft_putchar('=');
		ft_putstr(a->value);
		if (a->next != NULL)
			ft_putstr(",");
		a = a->next;
	}
	ft_putchar('\n');
}

static void		print_redirections(t_redirection const *r, size_t lvl)
{
	if (r == NULL)
		return ;
	print_n_char(' ', (lvl) * 2);
	ft_putstr("redirection(s):");
	while (r != NULL)
	{
		ft_putchar(' ');
		ft_putnbr(r->n);
		ft_putchar(' ');
		ft_putstr(get_token_def((t_token_id)r->type)->str);
		ft_putchar(' ');
		ft_putstr(r->word);
		if (r->next != NULL)
			ft_putstr(",");
		r = r->next;
	}
	ft_putchar('\n');
}

static void		print_simple_command(t_simple_command const *cmd, size_t lvl)
{
	char **it;

	if (cmd->argv[0] != NULL)
	{
		print_n_char(' ', (lvl) * 2);
		ft_putstr("command: ");
		ft_putendl(*cmd->argv);
		if (cmd->argv[1] != NULL)
		{
			print_n_char(' ', (lvl) * 2);
			ft_putstr("argument(s): ");
			it = cmd->argv + 1;
			while ((*it) != NULL)
			{
				if (it != cmd->argv + 1)
					ft_putchar(' ');
				it++;
			}
			ft_putchar('\n');
		}
	}
	print_assignments(cmd->assignments, lvl);
	print_redirections(cmd->redirections, lvl);
}

void			print_pipeline(t_simple_command const *pip, size_t lvl)
{
	if (pip == NULL)
	{
		print_n_char(' ', lvl * 2);
		ft_putendl("empty");
		return ;
	}
	if (pip->next == NULL)
	{
		print_simple_command(pip, lvl);
		return ;
	}
	print_n_char(' ', lvl * 2);
	ft_putendl("pipeline:");
	while (pip != NULL)
	{
		print_simple_command(pip, lvl + 1);
		pip = pip->next;
		if (pip != NULL)
		{
			print_n_char(' ', lvl * 2);
			ft_putchar('|');
			ft_putchar('\n');
		}
	}
}
