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

#ifndef EXECUTE_PIPELINE_H
# define EXECUTE_PIPELINE_H

t_error_id	execute_file(t_simple_command *cmd, size_t lvl);
t_error_id	execute_simple_command(t_simple_command *cmd, size_t lvl);
t_error_id	execute_pipeline(t_simple_command *pipeline, size_t lvl);

#endif
