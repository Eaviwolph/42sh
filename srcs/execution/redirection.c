/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 16:02:10 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 16:02:17 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include "utils.h"
#include <errno.h>

int					*save_stdin_stdout(void)
{
	static int std[2];

	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	return (std);
}

void				restore_stdin_stdout(int *std)
{
	dup2(std[0], STDIN_FILENO);
	close(std[0]);
	dup2(std[1], STDOUT_FILENO);
	close(std[1]);
}

int					choose_open(t_redir_type type, char *file)
{
	if (type == REDIR_OUTPUT)
		return (open(file, O_RDWR | O_CREAT | O_TRUNC, FILE_PERMISSION));
	else if (type == APPEND_OUTPUT)
		return (open(file, O_RDWR | O_CREAT | O_APPEND, FILE_PERMISSION));
	else
		return (open(file, O_RDONLY));
}

t_error_id			redirect(t_redirection *redirections, int *backup)
{
	t_error_id	ret;
	int			file_fd;

	set_error(NO_ERROR);
	ret = NO_ERROR;
	while (redirections)
	{
		file_fd = choose_open(redirections->type, redirections->word);
		if (file_fd < 0)
		{
			set_error(errno);
			ret = get_error();
			print_errno_error(ret, NULL, redirections->word);
			restore_stdin_stdout(backup);
			set_last_exit_status(1);
			return (ret);
		}
		else
		{
			dup2(file_fd, redirections->n);
			close(file_fd);
		}
		redirections = redirections->next;
	}
	return (ret);
}
