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

#ifndef TOKENIZER_STATE_H
# define TOKENIZER_STATE_H

# include "token.h"

typedef struct		s_tokenizer_state
{
	char		*input;
	char const	*current_char;
	char const	*word_start;
	char const	*op_start;
	t_token		*result;
	char const	*last_backslash;
	char const	*simple_quote_end;
	char const	*double_quote_end;
}					t_tokenizer_state;

#endif
