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

#ifndef TOKEN_ID_H
# define TOKEN_ID_H

typedef enum	e_token_id
{
	TOKEN_TOKID = 0,
	WORD_TOKID,
	ASSIGNMENT_WORD_TOKID,
	NEWLINE_TOKID,
	IO_NUMBER_TOKID,
	SEMI_TOKID,
	OR_TOKID,
	LESS_TOKID,
	GREAT_TOKID,
	AND_IF_TOKID,
	OR_IF_TOKID,
	DGREAT_TOKID
}				t_token_id;

#endif
