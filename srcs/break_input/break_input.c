/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 14:46:46 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 14:49:26 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "tokenizer.h"
#include "shell_env.h"
#include "ftsh.h"
#include "errors.h"

void	break_input(void)
{
	t_shell_env *shell_env;

	shell_env = get_shell_env();
	shell_env->tokens = tokenize(shell_env->input_string);
}
