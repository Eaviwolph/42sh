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

#ifndef CONTROL_CHARACTER_H
# define CONTROL_CHARACTER_H

char	*control_char_notation(char c);
void	print_control_char_notation(char c);

# define NUL	0x00
# define SOH	0x01
# define STX	0x02
# define ETX	0x03
# define EOT	0x04
# define ENQ	0x05
# define ACK	0x06
# define BEL	0x07
# define BS	0x08
# define TAB	0x09
# define LF	0x0A
# define VT	0x0B
# define FF	0x0C
# define CR	0x0D
# define SO	0x0E
# define SI	0x0F
# define DEL	0x7F

#endif
