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
#include <libft.h>
#include "variable.h"
#include "utils.h"

void	delete_redirections(t_redirection **redirs)
{
	t_redirection	*tmp;
	t_redirection	*it;

	it = *redirs;
	*redirs = NULL;
	while (it)
	{
		tmp = it;
		free(tmp->word);
		redirs = &tmp->next;
		it = *redirs;
		*redirs = NULL;
		free(tmp);
	}
}

void	delete_pipeline(t_simple_command **cmds)
{
	t_simple_command	*tmp;
	t_simple_command	*it;

	it = *cmds;
	*cmds = NULL;
	while (it)
	{
		tmp = it;
		delete_all_variables(&tmp->assignments);
		delete_redirections(&tmp->redirections);
		free_ptr_array(tmp->argv);
		cmds = &tmp->next;
		it = *cmds;
		*cmds = NULL;
		free(tmp);
	}
}

void	delete_and_or_list(t_and_or_list **ao_list)
{
	t_and_or_list	*tmp;
	t_and_or_list	*it;

	it = *ao_list;
	*ao_list = NULL;
	while (it)
	{
		tmp = it;
		delete_pipeline(&tmp->pipeline);
		ao_list = &tmp->next;
		it = *ao_list;
		*ao_list = NULL;
		free(tmp);
	}
}

void	delete_command_list(t_command_list **cmd_list)
{
	t_command_list	*tmp;
	t_command_list	*it;

	it = *cmd_list;
	*cmd_list = NULL;
	while (it)
	{
		tmp = it;
		delete_and_or_list(&tmp->and_or_list);
		cmd_list = &tmp->next;
		it = *cmd_list;
		*cmd_list = NULL;
		free(tmp);
	}
}
