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

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "execute_syntax_tree.h"
# include <libft.h>

/*
** FILE_PERMISSION same as 644
*/

# define FILE_PERMISSION (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)

int				*save_stdin_stdout();
t_error_id		redirect(t_redirection *redirections, int *backup);
void			restore_stdin_stdout(int *std);

#endif
