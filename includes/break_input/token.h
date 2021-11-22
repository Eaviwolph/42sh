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

#ifndef TOKEN_H
# define TOKEN_H

# include "token_def.h"
# include <stdlib.h>

typedef struct	s_token
{
	struct s_token		*next;
	t_token_def const	*type;
	char				*str;
}				t_token;

t_token			*construct_token(char const *str, char delim);
void			delete_token(t_token **token_addr);
void			delete_all_tokens(t_token **tokens_addr);
void			delete_tokens_array(t_token **tokens_array, size_t len);

void			print_token(t_token const *token);
void			print_tokens(t_token const *tokens);

t_token			**split_tokens_at(t_token const *tokens, t_token_id delim
	, size_t *len_addr);
t_token			**split_tokens_mult(t_token const *tokens
	, t_token_id *delims, size_t nbr_delims, size_t *len_addr);

t_token			*tokens_dup_until(t_token const *tokens, t_token const *stop);
size_t			count_token_type(t_token const *tokens, t_token_id type);
size_t			count_token_types(t_token const *tokens
	, t_token_id const *types, size_t nbr_types);
bool			token_is_one_of_types(t_token const *token
	, t_token_id const *types, size_t nbr_types);
t_token			*trim_newlines(t_token const *tokens);
t_token			*copy_token(t_token const *src);
t_token			*copy_all_tokens(t_token const *src);

#endif
