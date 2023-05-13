/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 20:30:57 by byoshimo          #+#    #+#             */
/*   Updated: 2023/05/13 19:39:15 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error(t_token **token_list, t_ms *ms, char c)
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

void	change_dollar_back(t_token *token_list)
{
	int		i;
	int		j;
	t_token	*aux;

	aux = token_list;
	while (aux)
	{
		i = 0;
		while (aux->token[i])
		{
			j = 0;
			while (aux->token[i][j])
			{
				if (aux->token[i][j] == DOLLAR_VAR)
					aux->token[i][j] = '$';
				j++;
			}
			i++;
		}
		aux = aux->next;
	}
}
