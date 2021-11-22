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

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "tokenizer_state.h"

t_token		*tokenize(char const *input);

void		apply_rules(t_tokenizer_state *state);
bool		apply_rules_2(t_tokenizer_state *state);
bool		apply_rules_3(t_tokenizer_state *state, char c);
void		delimit_token(t_tokenizer_state *state);
void		print_tokenizer_state(t_tokenizer_state *state);

#endif
