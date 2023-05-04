/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucade-s <lucade-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 20:30:57 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/04 16:15:42 by lucade-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error(t_token **token_list, t_ms **ms, char c)
{
	ft_putstr_fd("bilu: syntax error near unexpected token ", 2);
	if (c == '\n')
		ft_putstr_fd("'newline'\n", 2);
	else
	{
		ft_putchar_fd('\'', 2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd("'\n", 2);
	}
	exit_program(token_list, ms);
}
