/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:34:51 by asenat            #+#    #+#             */
/*   Updated: 2017/06/26 15:35:03 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "libft.h"
#include "uint.h"
#include <stdlib.h>

t_error const			*get_error_defs(void)
{
	static t_error const errors[TOTAL_ERROR_COUNT] =
	{{ TOO_MANY_ARGS, "too many arguments" },
		{ NEED_ARG, "option requires an argument" },
		{ NEED_NUM, "numeric argument required" },
		{ OUT_OF_RANGE, "history position out of range" },
		{ INVALID_OPTION, "invalid option" },
		{ EV_NOT_FOUND, "event not found"},
		{ BAD_WD_SPEC, "bad word specifier"},
		{ SUBST_FAIL, "substitution failed"},
		{ ANRW, "cannot use more than one of -anrw"},
		{ PERM_DENIED, "permission denied" },
		{ NO_SUCH_FILE, "no such file or directory" },
		{ IS_DIR, "is a directory" },
		{ UNMATCHED_SINGLE_QUOTE, "syntax error: unmatched '"},
		{ UNMATCHED_DOUBLE_QUOTE, "syntax error: unmatched \""},
		{ UNMATCHED_BACKQUOTE, "syntax error: unmatched `"},
		{ UNEXPECTED_SEMI, "syntax error: near unexpected ;"},
		{ UNEXPECTED_IF, "syntax error: near unexpected && or ||"},
		{ UNEXPECTED_PIPE, "syntax error: near unexpected |"},
		{ UNEXPECTED_TOKEN, "syntax error: near unexpected token"}
	};

	return (errors);
}
