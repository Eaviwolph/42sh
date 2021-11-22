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

#ifndef SYNTAX_TREE_H
# define SYNTAX_TREE_H

# include "variable.h"
# include "uint.h"
# include "break_input/token.h"

typedef enum	e_ao_type
{
	AO_OR = OR_IF_TOKID,
	AO_AND = AND_IF_TOKID,
	AO_END = TOKEN_TOKID
}				t_ao_type;

typedef enum	e_redir_type
{
	REDIR_OUTPUT = GREAT_TOKID,
	REDIR_INPUT = LESS_TOKID,
	APPEND_OUTPUT = DGREAT_TOKID
}				t_redir_type;

typedef struct		s_redirection
{
	struct s_redirection	*next;
	int						n;
	t_redir_type			type;
	char					*word;
}					t_redirection;

void				delete_redirections(t_redirection **redirs);

typedef struct		s_simple_command
{
	struct s_simple_command	*next;
	t_variable				*assignments;
	t_redirection			*redirections;
	char					**argv;
}					t_simple_command;

void				delete_pipeline(t_simple_command **cmds);

typedef struct		s_and_or_list
{
	struct s_and_or_list	*next;
	t_simple_command		*pipeline;
	t_ao_type				separation_type;
}					t_and_or_list;

void				delete_and_or_list(t_and_or_list **ao_list);

typedef struct		s_command_list
{
	struct s_command_list	*next;
	t_and_or_list			*and_or_list;
}					t_command_list;

void				delete_command_list(t_command_list **cmd_list);

#endif
