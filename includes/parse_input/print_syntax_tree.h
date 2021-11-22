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

#ifndef PRINT_SYNTAX_TREE_H
# define PRINT_SYNTAX_TREE_H

# include "syntax_tree.h"

void	print_command_list(t_command_list const *cmd_list, size_t lvl);
void	print_pipeline(t_simple_command const *pip, size_t lvl);

#endif
